.text
    main:
        li $2,10
        li $3,11
        li $4,2
        li $5,6
        li $6,2#5个待排序的数
        li $7,0#计数器
        li $8,0#存放比较结果
        li $9,0#交换的中间寄存器
    loop:
    beq $7,6,end
    addi $7,$7,1
    comp_23:
        slt $8,$2,$3
        beq $8,1,comp_34
        move $9,$2
        move $2,$3
        move $3,$9
    comp_34:
        slt $8,$3,$4
        beq $8,1,comp_45
        move $9,$3
        move $3,$4
        move $4,$9
    comp_45:
        slt $8,$4,$5
        beq $8,1,comp_56
        move $9,$4
        move $4,$5
        move $5,$9
    comp_56:
        slt $8,$2,$3
        beq $8,1,loop
        move $9,$5
        move $5,$6
        move $6,$9
        j loop
    end:
        li $v0,10
        syscall
    
