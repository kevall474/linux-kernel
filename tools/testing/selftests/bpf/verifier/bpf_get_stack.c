{
	"bpf_get_stack return R0 within range",
	.insns = {
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 28),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),
	BPF_MOV64_IMM(BPF_REG_9, sizeof(struct test_val)/2),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),
	BPF_MOV64_IMM(BPF_REG_3, sizeof(struct test_val)/2),
	BPF_MOV64_IMM(BPF_REG_4, 256),
	BPF_EMIT_CALL(BPF_FUNC_get_stack),
	BPF_MOV64_IMM(BPF_REG_1, 0),
	BPF_MOV64_REG(BPF_REG_8, BPF_REG_0),
	BPF_ALU64_IMM(BPF_LSH, BPF_REG_8, 32),
	BPF_ALU64_IMM(BPF_ARSH, BPF_REG_8, 32),
	BPF_JMP_REG(BPF_JSGT, BPF_REG_1, BPF_REG_8, 16),
	BPF_ALU64_REG(BPF_SUB, BPF_REG_9, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_9),
	BPF_ALU64_IMM(BPF_LSH, BPF_REG_1, 32),
	BPF_ALU64_IMM(BPF_ARSH, BPF_REG_1, 32),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_3, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	BPF_MOV64_IMM(BPF_REG_5, sizeof(struct test_val)/2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_1, BPF_REG_5),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_1, 4),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_9),
	BPF_MOV64_IMM(BPF_REG_4, 0),
	BPF_EMIT_CALL(BPF_FUNC_get_stack),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_48b = { 4 },
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
},
{
	"bpf_get_task_stack return R0 range is refined",
	.insns = {
	BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_1, 0),
	BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_6, 0), // ctx->meta->seq
	BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_1, 8), // ctx->task
	BPF_LD_MAP_FD(BPF_REG_1, 0), // fixup_map_array_48b
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_9, BPF_REG_0), // keep buf for seq_write
	BPF_MOV64_IMM(BPF_REG_3, 48),
	BPF_MOV64_IMM(BPF_REG_4, 0),
	BPF_EMIT_CALL(BPF_FUNC_get_task_stack),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_9),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_0),
	BPF_EMIT_CALL(BPF_FUNC_seq_write),

	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_TRACING,
	.expected_attach_type = BPF_TRACE_ITER,
	.kfunc = "task",
	.runs = -1, // Don't run, just load
	.fixup_map_array_48b = { 3 },
},
