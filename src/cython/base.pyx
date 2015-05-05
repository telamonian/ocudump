from libcpp cimport bool
from libcpp.vector cimport vector
from libc.stdint cimport uint32_t  #, int64_t

cimport ocudump_cython

#import lm_cython; reactionModel = lm_cython.ReactionModel(); hdf5File = lm_cython.Hdf5File('foo.lm'); hdf5File.getReactionModel(reactionModel); reactionModel.number_species()