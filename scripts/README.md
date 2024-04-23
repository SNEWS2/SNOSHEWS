This folder contains a number of scripts that either use SNOSHEWS or make / compile the data for / from SNOSHEWS

If you wish SNOSHEWS to output data as it does the calculation then, first, make sure to set the variable ID.outputfilenamestem. 
For example 

ID.outputfilenamestem = "./out/SNOSHEWS"

will output the data in a folder called "out" in the same folder as the code being run and all filenames will begin with 
the string "SNOSHEWS". Second, set the variable

ID.outputflag = True        # set to True if output is desired


