.text
    main:
        li $2,0#Fibonacci���еĵ�1��
        li $3,1#Fibonacci���еĵ�2��
        li $4,9#��Ҫ�����Fibonacci���е���
        li $5,2#������
        beq $4,1,patch
    judge:
        beq $5,$4,end#�ж��Ƿ�ָ����
        bne $5,$4,caculate
    caculate:
        add $6,$2,$3
        move $2,$3
        move $3,$6#������һ��
        addi $5,$5,1#��������1
        j judge
    patch:
        li $3,0
    end:
        move $1,$3
        li $v0,10
        syscall
        
    
    
    
