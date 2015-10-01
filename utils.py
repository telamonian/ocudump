# aspects of this build system are based on https://github.com/PySide/pyside-setup
from distutils import log
from distutils.errors import DistutilsExecError, DistutilsOptionError, DistutilsSetupError
from distutils.spawn import spawn
import os,sys
import struct
import subprocess

import popenasync

def IsPython64Bit():
    return (struct.calcsize("P") == 8)

def OptionValue(name):
    for index, option in enumerate(sys.argv):
        if option == '--' + name:
            if index+1 >= len(sys.argv):
                raise DistutilsOptionError(
                    'The option %s requires a value' % option)
            value = sys.argv[index+1]
            sys.argv[index:index+2] = []
            return value
        if option.startswith('--' + name + '='):
            value = option[len(name)+3:]
            sys.argv[index:index+1] = []
            return value
    env_val = os.getenv(name.upper().replace('-', '_'))
    return env_val

def RunProcess(args, cwd=None, initial_env=None):
    def _log(buffer, checkNewLine=False):
        endsWithNewLine = False
        if buffer.endswith('\n'):
            endsWithNewLine = True
        if checkNewLine and buffer.find('\n') == -1:
            return buffer
        lines = buffer.splitlines()
        buffer = ''
        if checkNewLine and not endsWithNewLine:
            buffer = lines[-1]
            lines = lines[:-1]
        for line in lines:
            log.info(line.rstrip('\r'))
        return buffer

    _log("Running process: {0}".format(" ".join([(" " in x and '"{0}"'.format(x) or x) for x in args])))

#     if sys.platform != "win32":
#         try:
#             spawn(args)
#             return 0
#         except DistutilsExecError:
#             return -1

    shell = False
    if sys.platform == "win32":
        shell = True

    if initial_env is None:
        initial_env = os.environ

    proc = popenasync.Popen(args,
        cwd = cwd,
        stdin = subprocess.PIPE,
        stdout = subprocess.PIPE,
        stderr = subprocess.STDOUT,
        universal_newlines = 1,
        shell = shell,
        env = initial_env)

    log_buffer = None;
    while proc.poll() is None:
        log_buffer = _log(proc.read_async(wait=0.1, e=0))
    if log_buffer:
        _log(log_buffer)

    proc.wait()
    return proc.returncode

def WrappedMkdir(d, mode=0755):
    try:
        os.mkdir(d, mode)
    except OSError:
        pass
    
def WrappedMakedirs(d, mode=0755):
    try:
        os.makedirs(d, mode)
    except OSError:
        pass