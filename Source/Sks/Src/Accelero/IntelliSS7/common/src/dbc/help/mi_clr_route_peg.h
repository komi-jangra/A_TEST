
ITU MTP3 Command

SYNOPSIS
    mi_clr_route_peg <dpc> <ni> [<Pegid> (or) <ALL/all>]

DESCRIPTION
    Reset a particular mtp3 route peg.

PARAMETERS

    dpc     destination point code 
    ni      network indicator 
    Pegid   the peg id that needs to be reset 

NOTE
    The Route Pegs-ids are:

         PEG_MTP3_DPC_TFA_TX                          0
         PEG_MTP3_DPC_TFA_RX                          1
         PEG_MTP3_DPC_TFP_TX                          2
         PEG_MTP3_DPC_TFP_RX                          3
         PEG_MTP3_DPC_RST_TX                          4
         PEG_MTP3_DPC_RST_RX                          5
         PEG_MTP3_DPC_TFR_RX                          6
         PEG_MTP3_DPC_TFC_TX                          7
         PEG_MTP3_DPC_TFC_RX                          8
         PEG_MTP3_DPC_SIF_TX                          9

         ALL_MTP3_PEGS                            99 

EXAMPLE
      >> mi_clr_route_peg 1 0 all
      Clearing All MTP3  Pegs for dpc 1 ni 0 
