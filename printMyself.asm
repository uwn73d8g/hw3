; addi   r1 r0 datalabel   # this immediate has value equal to the
;                                  # location of the label
;         lw     r2 r0 r1          # fetch data
;         printr r2

;         # for (r2=0; r2<10; r2++) { printf("%d", r2); }
        
;         addi   r1 r0 $10   # r1 = 10
;         xor    r2 r0 r0    # r2 = 0
; top:    printr r2
;         addi   r2 r2 $1    # r2++
;         cmp    r0 r2 r1    # r2 < 10 ?
;         blt    :top        # the leading ':' means "subtract current PC"
;                            # from value of the label
        
;         # immediates can be 'label' or ':label' or
;         # hex or decimal constants
;         addi   r1  r0 $99        # decimal 99
;         addi   r1  r0 0xff       # hex 0x00ff (the immediate is 12 bits)
;         addi   r1  r0 0xfff      # hex 0xffff (the immediate is sign extended)

;         stop

; datalabel:
;         nop                # a single byte of value 0x04
;         stop               # a single byte of value 0x00