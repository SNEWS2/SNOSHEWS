![image](https://github.com/SNEWS2/SNOSHEWS/assets/44247426/b7afb17b-b242-404e-ba54-d6a0fd447257)
Image by dreamstudio.ai


1) You will need the python-devel, pybind11 and setuptools packages

2) Modify setup.py to use the correct libraries and paths. 

3) To compile enter 

sudo python3 setup.py install 

4) If you don't want to sudo you may want to use the option

--install-lib=destination/directory/

TROUBLESHOOTING:

6) You may have to set the PYTHONPATH environment variable to your PWD
   and/or wherever the SNOSHEWS module was installed

7) If the script cannot find the module you may need to put the *.so library in the same directory
   as your script. The *.so library is in one of the subfolders in the build directory. 

9) You may want to set the OMP_NUM_THREADS environment variable to a reasonable number


