.name "zork"
.comment "I'M ALIIIIVE"

l2:		
		sti r1,%:live,%1
		and r1, 10, r1

		live %1_
		zjmp %live
live:
