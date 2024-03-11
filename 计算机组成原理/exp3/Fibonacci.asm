.text
    main:
        li $2,0#Fibonacci数列的第1项
        li $3,1#Fibonacci数列的第2项
        li $4,9#所要计算的Fibonacci数列的项
        li $5,2#计数器
        beq $4,1,patch
    judge:
        beq $5,$4,end#判断是否到指定项
        bne $5,$4,caculate
    caculate:
        add $6,$2,$3
        move $2,$3
        move $3,$6#计算下一项
        addi $5,$5,1#计数器加1
        j judge
    patch:
        li $3,0
    end:
        move $1,$3
        li $v0,10
        syscall
        
    
    
    
