
        # for (r2=0; r2<10; r2++) { printf("%d", r2); }
        
        addi   r1 r0 $10   # r1 = 10
        xor    r2 r0 r0    # r2 = 0
top:    printr r2
        addi   r2 r2 $1    # r2++
        cmp    r0 r2 r1    # r2 < 10 ?
        blt    :top        # the leading ':' means "subtract current PC"
                           # from value of the label
        stop
