        .data
prompt1: .asciiz "Enter the number of values to be read\n"
error:   .asciiz "Value must be between 1 and 10\n"
prompt2: .asciiz "Enter " 
prompt3: .asciiz " integer values, one per line\n"
summsg:  .asciiz "     Sum is: "
minmsg:  .asciiz "     Min is: "
maxmsg:  .asciiz "     Max is: "
meanmsg: .asciiz "    Mean is: "
varmsg:  .asciiz "Variance is: "
newline: .asciiz "\n"
.align 10
array:   .space 40              	

        .text
        .globl main

# Main function
main:
	# Starting prompt
	la $a0, prompt1            	
    	jal prtmsg                 	

get_num:
    	li $v0, 5                  	
    	syscall
    	move $t0, $v0              	
    	blt $t0, 1, error_reprompt 	# If number < 1, show error
    	bgt $t0, 10, error_reprompt 	# If number > 10, show error

    	# Integer values prompt
    	la $a0, prompt2            	
    	jal prtmsg

    	move $a0, $t0
    	li $v0, 1
    	syscall

    	la $a0, prompt3
    	jal prtmsg                 	

    	# Read values
    	la $a0, array              	
    	move $a1, $t0              	
    	jal readvals               	

    	# Calculates the sum
    	la $a0, array              	
    	move $a1, $t0              	
    	jal calcsum                	
    	move $t1, $v0              	

    	# Finds the min
    	la $a0, array              	
    	move $a1, $t0              	
    	jal findmin               	

    	# Finds the max
    	la $a0, array              	
    	move $a1, $t0              	
    	jal findmax                	

    	# Calculates mean
    	move $a0, $t1              	
    	move $a1, $t0              	
    	jal calcmean               	
    	mov.s $f12, $f0            	# Stores mean in $f12

    	# Calculates variance
    	la $a0, array              	
    	move $a1, $t0              	
    	jal calcvar                	

    	jr $ra                     	

error_reprompt:
    	la $a0, error              	
    	jal prtmsg                 	
    	j get_num                  	

# Prints a message passed in $a0
prtmsg:

    	li $v0, 4                  	
    	syscall
    	jr $ra                     	

# Prints a message followed by an integer
# $a0 = message address, $a1 = int
prtintmsg:
    	addi $sp, $sp, -4
    	sw $ra, 0($sp)

    	jal prtmsg                 	
    	move $a0, $a1              	
    	li $v0, 1                  	
    	syscall
    	la $a0, newline            	
    	jal prtmsg                 	

    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	jr $ra                     	

# Prints a message followed by a floating point value
# $a0 = message address, $f12 = float
prtfpmsg:
    	addi $sp, $sp, -4
    	sw $ra, 0($sp)

    	jal prtmsg                 	
    	li $v0, 2                  	
    	syscall
    	la $a0, newline            	
    	jal prtmsg                 	

    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	jr $ra                     	

# Reads n values into the array
# $a0 = array, $a1 = n
readvals:
    	move $t0, $a1              	
    	li $t4, 0                  	
read_loop:
    	beq $t4, $t0, end_read     	
    	li $v0, 5                  	
    	syscall
    	sw $v0, 0($a0)             	
    	addi $a0, $a0, 4           	
    	addi $t4, $t4, 1           	
    	j read_loop                	
end_read:
    	jr $ra                     	

# Finds the sum
# $a0 = array, $a1 = n
calcsum:
    	addi $sp, $sp, -4
    	sw $ra, 0($sp)

    	move $t0, $a1
    	li $v0, 0                  	
    	li $t1, 0                  	
sum_loop:
    	beq $t1, $t0, end_sum      	
    	lw $t2, 0($a0)             	
    	add $v0, $v0, $t2          	
    	addi $a0, $a0, 4           	
    	addi $t1, $t1, 1           	
    	j sum_loop                 	
end_sum:
    	la $a0, summsg             	
    	move $a2, $v0              	
    	jal prtintmsg
        
    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	jr $ra

# Finds minimum value
# $a0 = array, $a1 = n
findmin:
    	addi $sp, $sp, -4
    	sw $ra, 0($sp)

    	move $t0, $a1
    	lw $t2, 0($a0)             	
    	li $t1, 1                  	
min_loop:
    	beq $t1, $t0, end_min      	
    	addi $a0, $a0, 4
    	lw $t3, 0($a0)             	
    	bge $t2, $t3, update_min   	# If element < min, update min
next_min:
    	addi $t1, $t1, 1           	# Increment counter
    	j min_loop                 	
update_min:
    	move $t2, $t3              	
    	j next_min
end_min:
    	la $a0, minmsg             	
    	move $a1, $t2              	
    	jal prtintmsg              	

    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	jr $ra                     

# Finds maximum value
# $a0 = array, $a1 = n
findmax:
    	addi $sp, $sp, -4
    	sw $ra, 0($sp)

    	move $t0, $a1
    	lw $t2, 0($a0)             	
    	li $t1, 1                  	
max_loop:
    	beq $t1, $t0, end_max      	
    	addi $a0, $a0, 4
    	lw $t3, 0($a0)             	
    	ble $t2, $t3, update_max   	
next_max:
    	addi $t1, $t1, 1           	
    	j max_loop                 	
update_max:
    	move $t2, $t3              	
    	j next_max
end_max:
    	la $a0, maxmsg             	
    	move $a1, $t2              	
    	jal prtintmsg              	

    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	jr $ra

# Finds the mean
# $a0 = sum, $a1 = n
calcmean:
    	addi $sp, $sp, -8
    	sw $ra, 4($sp)
	sw $s0, 0($sp)

    	mtc1 $a2, $f4              	
    	mtc1 $a1, $f6              	
    	cvt.s.w $f4, $f4           	
    	cvt.s.w $f6, $f6           	
    	div.s $f0, $f4, $f6        	# Calculate mean
    	la $a0, meanmsg            	
    	mov.s $f12, $f0             	
    	jal prtfpmsg               	

	lw $s0, 0($sp)
    	lw $ra, 4($sp)
    	addi $sp, $sp, 8
    	jr $ra                      

# Find the variance
# $a0 = array, $a1 = n, $f12 = mean
calcvar:
    	addi $sp, $sp, -8
	sw $ra, 4($sp)
    	sw $s0, 0($sp)

    	li $t1, 0                  	
    	li.s $f4, 0.0              	
var_loop:
    	beq $t1, $a1, var_done     	
    	lw $t2, 0($a0)             	
    	mtc1 $t2, $f6              	
    	cvt.s.w $f6, $f6           	
    	sub.s $f8, $f6, $f12        	
    	mul.s $f8, $f8, $f8        	
    	add.s $f4, $f4, $f8        	
    	addi $a0, $a0, 4           	
    	addi $t1, $t1, 1           	
    	j var_loop                 	
var_done:
    	mtc1 $a1, $f10             	
    	cvt.s.w $f10, $f10         	
    	div.s $f4, $f4, $f10      	
    	la $a0, varmsg             	
    	mov.s $f12, $f4             	
    	jal prtfpmsg               	

	lw $s0, 0($sp)
   	lw $ra, 4($sp)
    	addi $sp, $sp, 8
    	jr $ra