start:  addi    r3  r0  start
        addi    r4  r0  end

top:    printm  r0  r3  r0
        addi    r3  r3  $2
        cmp     r0  r3  r4
        blt     :top 

end:    stop