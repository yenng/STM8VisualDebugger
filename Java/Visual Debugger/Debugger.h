typedef enum RegisterName RegisterName;
enum RegisterName {
  UNKNOWN_REG,
  A_REG,
  X_REG,
  Y_REG,
  SP_REG,
  PC_REG,
  CC_REG,
};

typedef enum StallReason StallReason;
enum StallReason {
  NOT_STALLED,
  STEP_STALL,
  SOFTWARE_BREAKPOINT,
  HARDWARE_BREAKPOINT,
};


/**
 * Write data into STM8 flash memory
 * @return 1 = success; 0 = failure
 */
int stm8FlashData(char *data, int startAddress, int size);

/**
 * Halt the STM8 CPU and return the STM8's PC register
 * @note The STM8 document call this 'stall' or 'abort'
 */
int stm8Halt(void);

/**
 * Determine if the STM8 CPU has stalled
 */
StallReason stm8HasCpuStalled(void);

/**
 * Resume STM8 CPU from the current PC address
 */
void stm8Resume(void);

/**
 * Run from the given address
 */
void stm8Run(int address);

/**
 * Assembly step 'count' times and return the STM8's PC register
 */
int stm8Step(int count);

/**
 * Read one byte (8 bit) of the STM8's memory content
 */
int stm8ReadByte(void);

/**
 * Read one half-word (16 bit) of the STM8's memory content
 * @note STM8 store data in big-endian format. However, the PC
 *       is in little-endian format
 */
int stm8ReadHalfWord(void);

/**
 * Read one word (32 bit) of the STM8's memory content
 * @note STM8 store data in big-endian format. However, the PC
 *       is in little-endian format
 */
int stm8ReadWord(void);

/**
 * Read register value
 */
int stm8ReadRegister(RegisterName register);

/**
 * Hardware reset the STM8 CPU.
 * @param haltOnReset indicates if STM8 should be halted on reset.
 *                    Non-zero means halt-on-reset, otherwise no halting.
 */
int stm8HardwareReset(int haltOnReset);

/**
 * Software reset the STM8 CPU
 * @param haltOnReset indicates if STM8 should be halted on reset
 *                    Non-zero means halt-on-reset, otherwise no halting.
 */
int stm8SoftwareReset(int haltOnReset);

/**
 * This lets STM8 CPU halts on executing BREAK instruction
 */
int stm8EnableSoftwareBreak(void);

/**
 * Set hardware breakpoint address
 */
void stm8SetInstructionBreakpointAt(int address);

/**
 * Set hardware breakpoint between address1 and address2, inclusively,
 * i.e, address1 <= bkpt <= address2.
 * @note address1 <= address2
 */
void stm8SetInstructionBreakpointsWithinRange(int address1, int address2);

/**
 * Set hardware breakpoint outside the range between address1 and address2,
 * inclusively, i.e, bkpt <= address1 or bkpt >= address2.
 * @note address1 <= address2
 */
void stm8SetInstructionBreakpointsOutsideRange(int address1, int address2);

/**
 * Set hardware data write watchpoint addresses. A data write on any address
 * will trigger the CPU stall.
 */
void stm8SetDataWriteWatchpointsAt(int address1, int address2);

/**
 * Set hardware data write watchpoint between address1 and address2,
 * inclusively, i.e, address1 <= write <= address2.
 * @note address1 <= address2
 */
void stm8SetDataWriteWatchpointsWithinRange(int address1, int address2);

/**
 * Set hardware data write watchpoint outside the range between address1
 * and address2, inclusively, i.e, write <= address1 or write >= address2.
 * @note address1 <= address2
 */
void stm8SetDataWriteWatchpointsOutsideRange(int address1, int address2);

/**
 * Set hardware data read watchpoint addresses. A data read on any address
 * will trigger the CPU stall.
 */
void stm8SetDataReadWatchpointsAt(int address1, int address2);

/**
 * Set hardware data read watchpoint between address1 and address2,
 * inclusively, i.e, address1 <= read <= address2.
 * @note address1 <= address2
 */
void stm8SetDataReadWatchpointsWithinRange(int address1, int address2);

/**
 * Set hardware data read/write watchpoint outside the range between address1
 * and address2, inclusively, i.e, read <= address1 or read >= address2.
 * @note address1 <= address2
 */
void stm8SetDataReadWatchpointsOutsideRange(int address1, int address2);

/**
 * Set hardware data read watchpoint addresses. A data read/write on any
 * address will trigger the CPU stall.
 */
void stm8SetDataReadWriteWatchpointsAt(int address1, int address2);

/**
 * Set hardware data read/write watchpoint between address1 and address2,
 * inclusively, i.e, address1 <= read <= address2.
 * @note address1 <= address2
 */
void stm8SetDataReadWriteWatchpointsWithinRange(int address1, int address2);

/**
 * Set hardware data read/write watchpoint outside the range between address1
 * and address2, inclusively, i.e, read/write <= address1 or
 * read/write >= address2.
 * @note address1 <= address2
 */
void stm8SetDataReadWriteWatchpointsOutsideRange(int address1, int address2);