.text
    main:
    	sll $0,$0,0
        addi $2,$0,5#������
        addi $3,$0,5#����
        addi $4,$0,0#��$4����ʾR0(ǰxλ)
        add $5,$0,$3#��$5����ʾR1(�м�yλ)
        addi $6,$0,0#����λZ
        addi $7,$0,0#������
        addi $8,$0,0#��λ����1
        addi $9,$0,0#��λ����2
    loop:
        beq $7,32,end
        addi $7,$7,1#ѭ��32��
        andi $8,$5,0x00000001
        andi $9,$6,0x80000000
        beq $8,0x00000000,choice0
        beq $8,0x00000001,choice1
    choice0:
        beq $9,0x00000000,case3
        beq $9,0x80000000,case1
    choice1:
        beq $9,0x00000000,case2
        beq $9,0x80000000,case3#���R1�����1λ��Z��������ת
    case1:
        addu $4,$4,$2
        j move_bit#01���
    case2:
        subu $4,$4,$2
        j move_bit#10���
    case3:
        j move_bit#00����11���
    move_bit:
        srl $6,$6,1
        andi $8,$5,0x00000001
        beq $8,0x00000001,change_Z
        bne $8,0x00000001,set_R1
    change_Z:
        addi $6,$6,0x80000000#��λZ��ͬʱ��R1���λ����Z
    set_R1:
        srl $5,$5,1
        andi $8,$4,0x00000001
        beq $8,0x00000001,change_R1
        bne $8,0x00000001,set_R0
    change_R1:
        addi $5,$5,0x80000000#��λR1,ͬʱ��R0���λ����R1���λ
    set_R0:
        sra $4,$4,1#������λR0
        j loop
    end:
        addi $0, $0,0
        
