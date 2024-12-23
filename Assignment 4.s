.data

vector1:
	.space 40
vector2:
	.space 40
prompt:
	.asciiz "Enter the number of elements in each vector: "
error_1:
	.asciiz "Exiting since the number of elements must be >= 1.\n"
error_10:
	.asciiz "Exiting since the number of elements must be <= 10.\n"
first_msg:
	.asciiz "Enter integer values one per line.\n"
sec_msg:
	.asciiz "Enter another integer values one per line.\n"
out_sum:
	.asciiz "The vector sum is:\n"
out_product:
	.asciiz "The vector product is:\n"
newline:
	.asciiz "\n"


	.text
	.globl main
main:
	# starting prompt
	li $v0, 4		# syscall for printing string
	la $a0, prompt		# loads address of prompt string
	syscall			# prints

	li $v0, 5		# syscall to read int
	syscall
	move $t0, $v0		# store elements in $t0

	# checks for first error
	li $t1, 1
	blt $t0, $t1, error_1

	# checks for second error
	li $t1, 10
	bgt $t0, $t1, error_10

	# Prompt and read first set of ints
	li $v0, 4
	la $a0, first_msg
	move $a1, $t0
	syscall

	# Read set of ints
	move $t2, $t0		# $t2 holds number of ints
	la $t3, vector1		# $t3 start of vector1

vector1_loop:
	beqz $t2, vector2_prompt	# if read, goes to vector 2
	li $v0, 5
	syscall
	sw $v0, 0($t3)		# stores input in vector1
	addi $t3, $t3, 4	# moves to next int
	addi $t2, $t2, -1	# decrements counter
	j vector1_loop		# repeats

vector2_prompt:
	# prompt and read second set of ints
	li $v0, 4
	la $a0, sec_msg
	# move $a1, $t0
	syscall

	# Reads second set of ints
	move $t2, $t0
	la $t3, vector2
vector2_loop:
	beqz $t2, compute	# if all are read, goes to compute
	li $v0, 5
	syscall
	sw $v0, 0($t3)
	addi $t3, $t3, 4
	addi $t2, $t2, -1
	j vector2_loop

compute:
	# Sum output
	li $v0, 4
	la $a0, out_sum
	syscall

	move $t2, $t0
	la $t3, vector1
	la $t4, vector2
print_sum:
	beqz $t2, print_product
	lw $t5, 0($t3)
	lw $t6, 0($t4)
	add $t7, $t5, $t6
	move $a0, $t7
	li $v0, 1
	syscall

	li $v0, 4
	la $a0, newline
	syscall

	addi $t3, $t3, 4
	addi $t4, $t4, 4
	addi $t2, $t2, -1
	j print_sum

print_product:
	# Vector output
	li $v0, 4
	la $a0, out_product
	syscall

	move $t2, $t0
	la $t3, vector1
	la $t4, vector2
product_loop:
	beqz $t2, exit_program
	lw $t5, 0($t3)
	lw $t6, 0($t4)
	mul $t7, $t5, $t6
	move $a0, $t7
	li $v0, 1
	syscall

	li $v0, 4
	la $a0, newline
	syscall

	addi $t3, $t3, 4
	addi $t4, $t4, 4
	addi $t2, $t2, -1
	j product_loop

exit_program:
	li $v0, 10
	syscall

# Error codes
error_less_one:
	li $v0, 4
	la $v0, error_1
	syscall
	li $v0, 10
	syscall

error_more_ten:
	li $v0, 4
	la $a0, error_10
	syscall
	li $v0, 10
	syscall

