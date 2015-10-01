# aspects of this build system are based on https://github.com/PySide/pyside-setup
from distutils.errors import DistutilsSetupError
from distutils.spawn import find_executable
from distutils.sysconfig import get_python_lib
import glob
import os,sys
from setuptools import setup
from setuptools.command.develop import develop
from setuptools.command.egg_info import egg_info
from setuptools.command.install import install

try:
    import multiprocessing
    NCPUS = multiprocessing.cpu_count()
except ImportError:
    NCPUS = 1

from utils import IsPython64Bit, OptionValue, RunProcess, WrappedMkdir, WrappedMakedirs

thisScriptDir = os.path.dirname(os.path.realpath(__file__))

OPTION_CMAKE = OptionValue("cmake")
if OPTION_CMAKE is None:
    OPTION_CMAKE = find_executable("cmake")
if OPTION_CMAKE is None or not os.path.exists(OPTION_CMAKE):
    raise DistutilsSetupError(
        "Failed to find cmake."
        " Please specify the path to cmake with --cmake parameter.")

class CustomEggInfoCommand(egg_info):
    '''
    customized egg_info command class
    deals with the fact that the build dir containing the cython-built ocudump library might not exist initially
    '''
    ocudumpCythonLibDir = os.path.join(thisScriptDir, 'build/src/cython')
    
    def __init__(self, dist, **kw):
        WrappedMakedirs(self.ocudumpCythonLibDir) 
        egg_info.__init__(self, dist, **kw)

class CustomSetupCommand:
    '''
    customized setup command base class
    meant to be used in a subclass that also inherits either setuptools.command.install.install or .develop
    '''
    cmakeBuildDir = os.path.join(thisScriptDir, 'build')
    
    def run(self):
        self._build_extension()
        
    def _build_extension(self):
        WrappedMkdir(self.cmakeBuildDir)
        
        if sys.platform=='win32':
            if IsPython64Bit():
                self.make_generator = 'Visual Studio 12 2013 Win64'
            else:
                self.make_generator = 'Visual Studio 12 2013'
        else:
            self.make_generator = 'Unix Makefiles'
        
        # Build module
        cmake_cmd = [
            OPTION_CMAKE,
            "-G", self.make_generator,
        #     "-DQT_QMAKE_EXECUTABLE=%s" % self.qmake_path,
        #     "-DBUILD_TESTS=%s" % self.build_tests,
        #     "-DDISABLE_DOCSTRINGS=True",
        #     "-DCMAKE_BUILD_TYPE=%s" % self.build_type,
        #     "-DCMAKE_INSTALL_PREFIX=%s" % self.install_dir,
            '..'
        ]
        
        make_cmd = [
            'cmake',
            '--build',
            '.',
            '--',
            '-j%d' % NCPUS
        ]
        
        if sys.platform == 'win32':
            cmake_cmd.append("-DCMAKE_BUILD_TYPE=%s" % 'Release')
            cmake_cmd.append("-DCMAKE_DEBUG_POSTFIX=_d")
            
        if RunProcess(cmake_cmd, cwd=self.cmakeBuildDir) != 0:
            raise DistutilsSetupError("Error setting up ocudump build with cmake")
        
        if RunProcess(make_cmd, cwd=self.cmakeBuildDir) != 0:
            raise DistutilsSetupError("Error make-ing ocudump build")
            
    def _writeLeapConfig(self):
        '''
        write config file to set path to leap motion packages
        '''
        if self.leapSDKEnvVar not in os.environ:
            raise EnvironmentError('%s%s' % ('You need to set the %s environment variable before installing ocumol, ' % self.leapSDKEnvVar,
                                             'e.g. you could run `LEAPSDK_DIR=/usr/local/LeapSDK pip install ocumol`'))
        leapSDKDir = os.environ.get(self.leapSDKEnvVar)
        with open('ocumol/leapConfig.py', 'w') as f:
            f.write("leapPath = '%s'" % os.path.join(leapSDKDir, 'lib'))
         
    def _writePymolrc(self):
        pymolrcPath = os.path.expanduser('~/.pymolrc')
        ocumolStartBumper = '#'*4 + 'START_OCUMOL_PLUGIN' + '#'*4
        ocumolEndBumper = '#'*4 + 'END_OCUMOL_PLUGIN' + '#'*4
        with open(os.path.join(thisScriptDir, 'pymolrc'), 'r') as f:
            ocumolPluginTxt = f.read()
        if not ReplaceBtwnLines(pymolrcPath, ocumolStartBumper, ocumolEndBumper, ocumolPluginTxt):
            AppendBlockToFile(pymolrcPath, ocumolStartBumper, ocumolEndBumper, ocumolPluginTxt)

class CustomDevelopCommand(CustomSetupCommand, develop):
    def run(self):
        CustomSetupCommand.run(self)
        develop.run(self)

class CustomInstallCommand(CustomSetupCommand, install):
    def run(self):
        CustomSetupCommand.run(self)
        install.run(self)

setup(
    author = 'Max Klein',
    cmdclass = {'develop': CustomDevelopCommand,
                'egg_info': CustomEggInfoCommand,
                'install': CustomInstallCommand},
    data_files = [(get_python_lib(), glob.glob('build/src/cython/*.so'))],
    description = 'lightweight library for dumping out tracking data from an Oculus Rift',
    license = 'UIOSL',
    name = "ocudump",
    package_dir = {'': 'build/src/cython'},
    zip_safe = False,
    )