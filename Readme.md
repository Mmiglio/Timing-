## Descripion
Code for the Timing lab. experience 

## Macro description

* `getDGTZ.C`: this macro allows you to read the tree produced by VERDI and get the digitizer and channel informations

## Data 
https://www.dropbox.com/home/TIMING

* `initial_operation_measurements.jpg` contains the first measurements of the two detectors' signals taken directly from the FAN-IN-FAN-OUT
* `initial_operation_test_daq.root` contains the data of the first aquisition (test)
# Energy Calibration
* `D1_OR.root` contains the data aquired when the detector D1 was connected to the coincidence unit (in OR) and the detector     D2 disconnected
* `D2_OR.root` contains the data aquired when the detector D2 was connected to the coincidence unit (in OR) and the detector     D1 disconnected
* `D1_D2_AND.root` contains the data acquired with detector D1 and detector D2 were connected in AND in the coincidence unit
# TAC calibration
5 minutes acquisitions.
* `delay_4ns.root` contains data acquired with delay in the DELAY UNIT set to 4 ns
* `delay_8ns.root` contains data acquired with delay in the DELAY UNIT set to 8 ns
* `delay_10ns.root` contains data acquired with delay in the DELAY UNIT set to 10 ns
* `delay_16ns.root` contains data acquired with delay in the DELAY UNIT set to 16 ns
* `delay_20ns.root` contains data acquired with delay in the DELAY UNIT set to 20 ns
* `delay_24ns.root` contains data acquired with delay in the DELAY UNIT set to 24 ns
* `delay_28ns.root` contains data acquired with delay in the DELAY UNIT set to 28 ns
* `tac_calibration.jpg` contains information of Gaussian fit performed with VERDI (in lab) used for calibration fit 
# Delay cable calibration
5 minutes acquisitions
* `cable_115mm.root` contains data acquired with a 115 mm cable in series to the one connecting the delay unit to the stop of the TAC
* `cable_215mm.root` contains data acquired with a 215 mm cable in series to the one connecting the delay unit to the stop of the TAC
* `cable_500mm.root` contains data acquired with a 500 mm cable in series to the one connecting the delay unit to the stop of the TAC
* `cable_605mm.root` contains data acquired with a 605 mm cable in series to the one connecting the delay unit to the stop of the TAC
* `cable_800mm.root` contains data acquired with a 800 mm cable in series to the one connecting the delay unit to the stop of the TAC
* `cable_1000mm.root` contains data acquired with a 1000 mm cable in series to the one connecting the delay unit to the stop of the TAC
# Time resolution as a function of CFTD external delay
10 minutes acquisitions
* `external_delay_3ns.root` contains data acquired with a 3 ns delay cable used as external delay of CFTD
* `external_delay_3-5ns.root` contains data acquired with a 3 ns delay cable + a 0.5 ns cable (in series) used as external delay of CFTD
* `external_delay_4ns.root` contains data acquired with a 4 ns delay cable used as external delay of CFTD
* `external_delay_4-5ns.root` contains data acquired with a 4 ns delay cable + a 0.5 ns cable (in series) used as external delay of CFTD
* `external_delay_5ns.root` contains data acquired with a 5 ns delay cable used as external delay of CFTD
# Time resolution as a function of energy range
* `Cobalt.root` contains data acquired during the night (20h acquisition) with Co60 source
# Speed of light
# Time resolution with digital CFTD
