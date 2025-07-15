---
title: 'SNOSHEWS: Supernova NeutrinO SHock Effects With SNEWPY'
tags:
  - Python
  - astronomy
  - supernova
  - neutrinos
authors:
  - name: Segev BenZvi
    orcid: 0000-0001-5537-4710
    affiliation: 1
  - name: Marta Colomer Molla
    orcid: 0000-0003-1801-8121
    affiliation: 2
  - name: Alec Habig
    affiliation: 3
    orcid: 0000-0002-1018-9383
  - name: James P. Kneller^[Corresponding author]
    orcid: 0000-0002-3502-3830
    affiliation: 4
  - name: Jost Migenda
    orcid: 0000-0002-5350-8049
    affiliation: 5
  - name: Kate Scholberg
    orcid: 0000-0002-7007-2021
    affiliation: 6
  - name: Andrey Sheshukov
    affiliation: 7
    orcid: 0000-0001-5128-9279
  - name: Jeff Tseng
    affiliation: 8
    orcid: 0000-0003-1731-5853
affiliations:
  - name: University of Rochester, Rochester, NY, USA
    index: 1
  - name: Université Libre de Bruxelles, Brussels, Belgium
    index: 2
  - name: University of Minnesota Duluth, Duluth, MN, USA
    index: 3
  - name: NC State University, Raleigh, NC, USA
    index: 4    
  - name: King’s College London, London, UK
    index: 5
  - name: Duke University, Durham, NC, USA
    index: 6
  - name: Joint Institute for Nuclear Research, Dubna, Russia
    index: 7
  - name: Oxford University, Oxford, UK
    index: 8
date: 1 September 2025
bibliography: paper.bib

---

# Summary

SNOSHEWS is a python module for calculating the effect of matter upon neutrinos i.e MSW effects, including the effects of shocks. It is a standalone module but it can also be used with SNEWPY 2.0 to add shock effects to supernova neutrino signals. 

# Statement of need

As neutrinos pass through the mantle of a supernova the matter alters the probability that neutrino of a given initial flavor would be detected as a final given flavor. Most of the time the neutrinos evolve adibatically and the probabilities can be computed analytically in this limit. However the presence of shock waves in the density profile of the supernova makes the evolution of the neutrinos through these shock features non-adibatic, and if there are several shcoks, phase effects can occur. SNOSHEWS (Supernova NeutrinO SHock Effects With SNEWPY) is a python module that calculates the effect of passing through an arbitrary density profile upon the neutrinos of a given energy and mixing paramaters. The effect is calculated by solving the Schrodinger equation for the neutrino evolution operator using a Hamiltonian composed of the 'vacuum term' and the MSW 'matter term', and assumes the neutrino starts at high density (i.e. at the proto-neutron star) and travels through the entire supernova mantle to the vacuum. Further details of the calculation can be found in the appendix of the in the SNEWPY 2.0 documentation. The output is in the form of tables of of the probability that a neutrino of a given initial state nu_j is detected as state nu_i. Output files of the probabilities as a function of distance traveled along the trajectroy are generated for each neutrino energy, and of the probabilities as a function of neutrino energy as the neutrino exit the star. 

# How to use SNOSHEWS

The SNOSHEWS.py example script in the doc folder shows how to use the module. SNOSHEWS can also be imported into the SNEWPY 2.0 software and is used in the `NumericalMSW' flavor transformation prescription. How to include SNOSHEWS with SNEWPY will be documented in the SNEWPY 2.0 documentation. 

As shown in the SNOSHEWS.py example script, to use SNOSHEWS the user must provide the two data files: the density profile as a function of radius through the supernova, and the electron fraction profile. In the example script SNOSHEWS uses profiles00585_stp.d and profiles00585_Ye.d as the input density and electron fraction profiles. This data was kindly provided by Tobias Fischer and the simulation which generated the data is described in [@2010A&A...517A..80F] 

Two other scripts are provided: "Create Profiles.ipynb" and "Process Profiles.py". The first generates supernova-like density profiles as a function of time according to an analytic prescription. It will save the data in a folder designated by the user, make figures of the density profiles, and stitch them together into a movie. The second will process each of the profiles through SNOSHEWS, read in the data, make a plot of two of the probabilities for the 10 MeV neutrinos, and then stitch the plots together into a movie. 

# Acknowledgements

This work is supported by the National Science Foundation “Windows on the Universe: the Era of Multi-Messenger Astrophysics” Program: “WoU-MMA:
Collaborative Research: A Next-Generation SuperNova Early Warning System for Multimessenger Astronomy” through Grant Nos. 1914448, 1914409, 1914447,
1914418, 1914410, 1914416, and 1914426. This work is also supported at NC State by U.S. Department of Energy grant DE-FG02-02ER41216, and at King’s College London by STFC.

# References

