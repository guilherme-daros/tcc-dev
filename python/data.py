picoW = {
    "P_idle" : 6.324e-3,
    "P_tx"   : 234e-3,      
    "P_uC"   : 104e-3,
    "t_tx"   : 25*0.1052e-3,
}

picoW_smallmodel = picoW | {
    "t_uC"   : 1834e-6,
}
picoW_bigmodel = picoW | {
    "t_uC"   : 58645e-6,
}
