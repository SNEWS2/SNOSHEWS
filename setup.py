# to use type "sudo python3 setup.SNOSHEWS.py installon the command line

#!/usr/bin/env python
#
# Licensed under a 3-clause BSD style license - see LICENSE.rst


import os
from distutils.command.sdist import sdist as DistutilsSdist
from setuptools import setup, find_packages
from setuptools.extension import Extension

#
# Begin setup
#
setup_keywords = dict()
#

setup_keywords['extras_require'] = {  # Optional
    'dev': ['pytest'],
    'docs':['numpydoc']
}

SNOSHEWS = Extension('SNOSHEWS',
                    define_macros = [('MAJOR_VERSION', '1'), ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/lib/python3.9/site-packages/pybind11/include', './src', './src/mstl', './src/mstl/math2', './src/mstl/math2/algebra', './src/mstl/math2/analysis', './src/mstl/math2/spline', './src/mstl/physics'],
                    libraries = ['stdc++', 'm', 'gomp', 'python3'],
                    library_dirs = ['/usr/lib64'],
                    extra_compile_args = ['-std=c++17', '-fopenmp', '-fPIC', '-nostartfiles'],
                    extra_link_args = ['-shared'],
                    sources = ['./src/SNOSHEWS.cpp', './src/adiabatic_basis.cpp', './src/eigenvalues.cpp', './src/flavour_basis.cpp', './src/input_class.SNOSHEWS.cpp', './src/jacobians.cpp', './src/mixing_angles.cpp', './src/output.SNOSHEWS.cpp', './src/output_matrix.SNOSHEWS.cpp', './src/parameters.cpp', './src/potentials.cpp', './src/RK.SNOSHEWS.cpp', './src/update.SNOSHEWS.cpp', './src/mstl/errors2.cpp', './src/mstl/messages.cpp', './src/mstl/miscellaneous functions.cpp', './src/mstl/stdarg2.cpp', './src/mstl/math2/algebra/column and row vectors.cpp', './src/mstl/math2/algebra/linear algebra.cpp', './src/mstl/math2/algebra/mmatrix.cpp', './src/mstl/math2/analysis/algorithm3.cpp', './src/mstl/math2/analysis/complex2.cpp', './src/mstl/math2/analysis/derivative.cpp', './src/mstl/math2/analysis/polynomial.cpp', './src/mstl/math2/analysis/roots.cpp', './src/mstl/math2/analysis/runge kutta.cpp', './src/mstl/math2/analysis/special functions.cpp', './src/mstl/math2/spline/discontinuous.cpp', './src/mstl/math2/spline/interpolation data.cpp', './src/mstl/physics/units and constants.cpp'])

setup_keywords['ext_modules'] = [SNOSHEWS]

#
# Run setup command.
#
setup(**setup_keywords)
