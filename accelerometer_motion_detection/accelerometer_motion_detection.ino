void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void MMA8452::initMMA8452(unsigned char fsr, unsigned char dr, unsigned char sr, unsigned char sc, unsigned char mt, unsigned char mdc)
{
    MMA8452Standby();

//Set up the full scale range to 2, 4, or 8g.
if ((fsr==2)||(fsr==4)||(fsr==8))
    writeRegister(XYZ_DATA_CFG, fsr >> 2);  
else
    writeRegister(XYZ_DATA_CFG, 0);

writeRegister(CTRL_REG1, readRegister(CTRL_REG1) & ~(0xF8));
if (dr<= 7)
    writeRegister(CTRL_REG1, readRegister(CTRL_REG1) | (dr << DR0));
if (sr<=3)
    writeRegister(CTRL_REG1, readRegister(CTRL_REG1) | (sr << ASLP_RATE0));

writeRegister(CTRL_REG2, readRegister(CTRL_REG2) | (LP << SMODS) | (LP << MODS) | (1 << SLPE));  //LOW POWER MODE IN SLEEP & ACTIVE STATES WITH LOWEST SAMPLING
writeRegister(ASLP_COUNT, sc);

// Set up interrupt 1 and 2: 1 = wake ups, 2 = data
writeRegister(CTRL_REG3, (1 << WAKE_FF_MT) | (1 << IPOL));  // Active high, push-pull interrupts, sleep wake up from motion detection
writeRegister(CTRL_REG4, (1 << INT_EN_ASLP) | (1 << INT_EN_FF_MT) |  (1 << INT_EN_DRDY));  // DRDY ENABLE SLP/AWAKE INTERRUPT (INTERRUPT THROWN WHENEVER IT CHANGES) & MOTION INTERRUPT TO KEEP AWAKE
writeRegister(CTRL_REG5, (1 << INT_CFG_ASLP) | (1 << INT_CFG_FF_MT));  // DRDY on INT1, ASLP_WAKE INT2, FF INT2
writeRegister(CTRL_REG5, readRegister(CTRL_REG5));

//SETUP THE MOTION DETECTION
writeRegister(FF_MT_CFG, 0xF8);     /*MOTION DETECTION AND LATCH THE 
                                    //RESULT WHEN IT HAPPENS AS OPPOSED 
                                    //TO COMBINATIONAL REAL TIME*/
    writeRegister(FF_MT_THS, mt);       //MOTION DETECTION THRESHOLDS 
    writeRegister(FF_MT_COUNT, mdc);    //TIME MOTION NEEDS TO BE 
                                        //PRESENT ABOVE THE THRESHOLD BEFORE INTERRUPT CAN BE ASSERTED

    MMA8452Active();
}
