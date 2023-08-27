


 #ifndef BIT_MATH_H_
 #define BIT_MATH_H_


#define SET_BIT(REG , BITNUM            REG |= 1U<<BITNUM
#define CLR_BIT(REG , BITNUM)           REG &= ~(1U<<BITNUM)
#define TOG_BIT(REG , BITNUM)           REG ^= 1U<<BITNUM
#define INSERT_BIT(reg, bit, value)     ((value)? (reg|=(1<<bit)) : (reg&=(~(1<<bit))))
#define GET_BIT(REG , BITNUM)           ( (REG >> BITNUM) & 1U )


 #endif /* BIT_MATH_H_ */
