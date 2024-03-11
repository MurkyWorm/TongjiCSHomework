.text

main:
addi $2,$0,0 #a[0]
addi $3,$0,1 #b[0]
addi $4,$0,0 #c[0]
addi $5,$0,1 #d[0]
addi $6,$0,0 #a[i]
addi $7,$0,1 #b[i]
addi $8,$0,0 #c[i]
addi $9,$0,1 #d[i]
addi $10,$0,0 #flag for count
addi $11,$0,240 #sum counts
addi $12,$0,4 #counter
addi $13,$0,3 #factor
lui $1,0x1001 #0x10010000 basic address
addu $1,$1,$0
sw $2,0($1)   
lui $1,0x1002
addu $1,$1,$0
sw $3,0($1)  
lui $1,0x1003
addu $1,$1,$0
sw $4,0($1)  
lui $1,0x1004
addu $1,$1,$0
sw $5,0($1)  

loop:
srl $14,$12,2 #i=count/4
add $6,$6,$14 #a[i]=a[i-1]+i
lui $1,0x1001
addu $1,$1,$12 #address+count
sw $6,0($1) 
mul $15,$13,$14 #3*i
add $7,$7,$15  #b[i]=b[i-1]+3i
lui $1,0x1002
addu $1,$1,$12
sw $7,0($1)  
slti $10,$12,80 #i<20?
bne $10,1,op2 #i>=20
lui $1,0x1003 #i<20
addu $1,$1,$12
sw $6,0($1)  #c[i]=a[i]
lui $1,0x1004
addu $1,$1,$12
sw $7,0($1) #d[i]=b[i]
addi $8,$6,0
addi $9,$7,0
j nxtloop

op2:
slti $10,$12,160 #i<40?
addi $1,$0,1
bne $10,$1,op3 #i>=40
add $8,$6,$7 #c[i]=a[i]+b[i]
lui $1,0x1003
addu $1,$1,$12
sw $8,0($1)
mul $9,$8,$6 #d[i]=a[i]*c[i]
lui $1,0x1004
addu $1,$1,$12
sw $9,0($1)
j nxtloop

op3:
mul $8,$6,$7 #c[i]=a[i]*b[i]
lui $1,0x1003
addu $1,$1,$12
sw $8,0($1)
mul $9,$8,$7 #d[i]=c[i]*b[i]
lui $1,0x1004
addu $1,$1,$12
sw $9,0($1)

nxtloop:
add $30,$8,$9 #e[i]=c[i]+d[i]
lui $1,0x1005
addu $1,$1,$12
sw $30,0($1)
addi $12,$12,4 #count+4
bne $12,$11,loop
