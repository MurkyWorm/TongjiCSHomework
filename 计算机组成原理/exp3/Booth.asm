.text
    main:
    	sll $0,$0,0
        addi $2,$0,5#被乘数
        addi $3,$0,5#乘数
        addi $4,$0,0#用$4来表示R0(前x位)
        add $5,$0,$3#用$5来表示R1(中间y位)
        addi $6,$0,0#辅助位Z
        addi $7,$0,0#计数器
        addi $8,$0,0#移位辅助1
        addi $9,$0,0#移位辅助2
    loop:
        beq $7,32,end
        addi $7,$7,1#循环32次
        andi $8,$5,0x00000001
        andi $9,$6,0x80000000
        beq $8,0x00000000,choice0
        beq $8,0x00000001,choice1
    choice0:
        beq $9,0x00000000,case3
        beq $9,0x80000000,case1
    choice1:
        beq $9,0x00000000,case2
        beq $9,0x80000000,case3#检查R1的最后1位和Z，进行跳转
    case1:
        addu $4,$4,$2
        j move_bit#01情况
    case2:
        subu $4,$4,$2
        j move_bit#10情况
    case3:
        j move_bit#00或者11情况
    move_bit:
        srl $6,$6,1
        andi $8,$5,0x00000001
        beq $8,0x00000001,change_Z
        bne $8,0x00000001,set_R1
    change_Z:
        addi $6,$6,0x80000000#移位Z，同时将R1最低位赋给Z
    set_R1:
        srl $5,$5,1
        andi $8,$4,0x00000001
        beq $8,0x00000001,change_R1
        bne $8,0x00000001,set_R0
    change_R1:
        addi $5,$5,0x80000000#移位R1,同时将R0最低位赋给R1最高位
    set_R0:
        sra $4,$4,1#算术移位R0
        j loop
    end:
        addi $0, $0,0
        
