.ORIG x4000
      AND R0, R0, #0
      ADD R0, R0, #4
      LEA R1, A
      LDW R1, R1, #0
      STW R0, R1, #0
      HALT
A     .FILL x3000	
      .END
