This folder contains a number of scripts that either use SNOSHEWS or make / compile the data for / from SNOSHEWS

In the SNOSHEWS_example.py script:

If you wish SNOSHEWS to output data as it does the calculation then, first, make sure to set the variable ID.outputfilenamestem. 
For example 

ID.outputfilenamestem = "./out/SNOSHEWS"

will output the data in a folder called "out" and all filenames will begin with the string "SNOSHEWS". Second, set the variable

ID.outputflag = True        

The code uses a density profile kindly provided by Tobias Fischer. The simulation used to generate the data is described in 
Fischer, Whitehouse, Mezzacappa, Thielemann1, and Liebendorfer in "Protoneutron star evolution and the neutrino-driven wind in 
general relativistic neutrino radiation hydrodynamics simulations" Astron & Astrophys 517, A80 (2010) 

It was modified as described in Lund & Kneller in "Combining collective, MSW, and turbulence effects in supernova neutrino flavor evolution" 
Phys. Rev. D 88, 023008 (2003). This is the profile seen in figure 2 of the paper. 



In the CreateProfiles.ipynb notbeook:

The formulae for the position of the shocks were fit to the shocks in a PUSH simulation kindly provided by Carla Frohlich. 

In the RunSNOSHOES.ipynb notbeook:
