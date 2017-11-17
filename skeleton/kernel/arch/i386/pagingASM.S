.text
.global reloadPaging
.type reloadPaging, @function
reloadPaging:
	movl %cr3, %eax
	movl %eax, %cr3
	ret