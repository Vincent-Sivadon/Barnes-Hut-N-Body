address;source_location;insn;indent
0x1120;:0;ENDBR64;
0x1124;:0;PUSH	%RBP;
0x1125;:0;MOV	$0x2,%EDI;
0x112a;:0;MOV	%RSP,%RBP;
0x112d;:0;PUSH	%R14;
0x112f;:0;PUSH	%R13;
0x1131;:0;PUSH	%R12;
0x1133;:0;PUSH	%R10;
0x1135;:0;PUSH	%RBX;
0x1136;:0;SUB	$0x18,%RSP;
0x113a;:0;CALL	10d0 <.plt.sec@start+0x20>;
0x113f;:0;XOR	%EAX,%EAX;
0x1141;:0;CALL	1c90 <init_system>;
0x1146;:0;LEA	0x1eb7(%RIP),%RCX;
0x114d;:0;LEA	0x1eb9(%RIP),%RDX;
0x1154;:0;LEA	0x1eb7(%RIP),%RSI;
0x115b;:0;MOV	$0x1,%EDI;
0x1160;:0;XOR	%EAX,%EAX;
0x1162;:0;CALL	1100 <.plt.sec@start+0x50>;
0x1167;:0;MOV	0x3ea2(%RIP),%RDI;
0x116e;:0;CALL	10f0 <.plt.sec@start+0x40>;
0x1173;:0;MOV	0x3ea7(%RIP),%EAX;
0x1179;:0;TEST	%EAX,%EAX;
0x117b;:0;JLE	13e1 <main+0x2c1>;
0x1181;:0;VXORPD	%XMM4,%XMM4,%XMM4;
0x1185;:0;XOR	%R13D,%R13D;
0x1188;:0;VMOVSD	%XMM4,-0x38(%RBP);
0x118d;:0;MOV	$-0x100000000,%R14;
0x1197;:0;NOPW	(%RAX,%RAX,1);
0x11a0;:0;CALL	10c0 <.plt.sec@start+0x10>;(0) 
0x11a5;:0;MOV	$0x80,%EDI;(0) 
0x11aa;:0;VMOVSD	%XMM0,-0x40(%RBP);(0) 
0x11af;:0;CALL	10e0 <.plt.sec@start+0x30>;(0) 
0x11b4;:0;VMOVAPD	0x1f04(%RIP),%YMM2;(0) 
0x11bc;:0;VPXOR	%XMM0,%XMM0,%XMM0;(0) 
0x11c0;:0;MOV	%RAX,%R12;(0) 
0x11c3;:0;VMOVUPD	%YMM2,(%RAX);(0) 
0x11c7;:0;VMOVDQU	%YMM0,0x40(%RAX);(0) 
0x11cc;:0;VMOVDQU	%YMM0,0x60(%RAX);(0) 
0x11d1;:0;MOV	0x1e88(%RIP),%RAX;(0) 
0x11d8;:0;MOV	%R12,%RDI;(0) 
0x11db;:0;MOV	%RAX,0x20(%R12);(0) 
0x11e0;:0;MOV	%RAX,0x28(%R12);(0) 
0x11e5;:0;MOV	%R14,0x30(%R12);(0) 
0x11ea;:0;MOVB	$0,0x38(%R12);(0) 
0x11f0;:0;VZEROUPPER;(0) 
0x11f3;:0;CALL	1850 <subdivide>;(0) 
0x11f8;:0;MOV	0x3e26(%RIP),%EAX;(0) 
0x11fe;:0;TEST	%EAX,%EAX;(0) 
0x1200;:0;JLE	121c <main+0xfc>;(0) 
0x1202;:0;XOR	%EBX,%EBX;(0) 
0x1204;:0;NOPL	(%RAX);(0) 
0x1208;:0;MOV	%EBX,%ESI;  (1) 
0x120a;:0;MOV	%R12,%RDI;  (1) 
0x120d;:0;INC	%EBX;  (1) 
0x120f;:0;CALL	1a80 <insertParticle>;  (1) 
0x1214;:0;CMP	%EBX,0x3e0a(%RIP);  (1) 
0x121a;:0;JG	1208 <main+0xe8>;  (1) 
0x121c;:0;MOV	%R12,%RDI;(0) 
0x121f;:0;CALL	2360 <simulate>;(0) 
0x1224;:0;CMPB	$0,0x38(%R12);(0) 
0x122a;:0;JE	13c0 <main+0x2a0>;(0) 
0x1230;:0;MOV	0x40(%R12),%RDI;(0) 
0x1235;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x123a;:0;MOV	0x48(%R12),%RDI;(0) 
0x123f;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1244;:0;MOV	0x50(%R12),%RDI;(0) 
0x1249;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x124e;:0;MOV	0x58(%R12),%RDI;(0) 
0x1253;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1258;:0;MOV	0x60(%R12),%RDI;(0) 
0x125d;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1262;:0;MOV	0x68(%R12),%RDI;(0) 
0x1267;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x126c;:0;MOV	0x70(%R12),%RDI;(0) 
0x1271;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1276;:0;MOV	0x78(%R12),%RDI;(0) 
0x127b;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1280;:0;MOV	%R12,%RDI;(0) 
0x1283;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x1288;:0;CALL	10c0 <.plt.sec@start+0x10>;(0) 
0x128d;:0;VSUBSD	-0x40(%RBP),%XMM0,%XMM0;(0) 
0x1292;:0;VADDSD	-0x38(%RBP),%XMM0,%XMM4;(0) 
0x1297;:0;VMOVSD	%XMM4,-0x38(%RBP);(0) 
0x129c;:0;MOV	%R13D,%EDX;(0) 
0x129f;:0;LEA	0x1d7e(%RIP),%RSI;(0) 
0x12a6;:0;MOV	$0x1,%EDI;(0) 
0x12ab;:0;MOV	$0x1,%EAX;(0) 
0x12b0;:0;CALL	1100 <.plt.sec@start+0x50>;(0) 
0x12b5;:0;MOV	0x3d54(%RIP),%RDI;(0) 
0x12bc;:0;INC	%R13D;(0) 
0x12bf;:0;CALL	10f0 <.plt.sec@start+0x40>;(0) 
0x12c4;:0;MOV	0x3d56(%RIP),%EAX;(0) 
0x12ca;:0;CMP	%R13D,%EAX;(0) 
0x12cd;:0;JG	11a0 <main+0x80>;(0) 
0x12d3;:0;MOV	0x3d4b(%RIP),%EDX;
0x12d9;:0;VXORPS	%XMM1,%XMM1,%XMM1;
0x12dd;:0;LEA	(%RDX,%RDX,2),%EDX;
0x12e0;:0;SAL	$0x7,%EDX;
0x12e3;:0;VCVTSI2SD	%EDX,%XMM1,%XMM0;
0x12e7;:0;VCVTSI2SD	%EAX,%XMM1,%XMM1;
0x12eb;:0;LEA	0x1d3b(%RIP),%RSI;
0x12f2;:0;MOV	$0x1,%EDI;
0x12f7;:0;VMULSD	0x1d99(%RIP),%XMM0,%XMM0;
0x12ff;:0;MOV	$0x1,%EAX;
0x1304;:0;VMULSD	%XMM1,%XMM0,%XMM1;
0x1308;:0;VMOVSD	-0x38(%RBP),%XMM0;
0x130d;:0;VDIVSD	%XMM0,%XMM1,%XMM1;
0x1311;:0;VMOVSD	%XMM1,-0x38(%RBP);
0x1316;:0;CALL	1100 <.plt.sec@start+0x50>;
0x131b;:0;VMOVSD	-0x38(%RBP),%XMM1;
0x1320;:0;LEA	0x1d1e(%RIP),%RSI;
0x1327;:0;VMOVAPD	%XMM1,%XMM0;
0x132b;:0;MOV	$0x1,%EDI;
0x1330;:0;MOV	$0x1,%EAX;
0x1335;:0;CALL	1100 <.plt.sec@start+0x50>;
0x133a;:0;MOV	0x3d2f(%RIP),%RDI;
0x1341;:0;CALL	10b0 <.plt.sec@start>;
0x1346;:0;MOV	0x3d2b(%RIP),%RDI;
0x134d;:0;CALL	10b0 <.plt.sec@start>;
0x1352;:0;MOV	0x3d27(%RIP),%RDI;
0x1359;:0;CALL	10b0 <.plt.sec@start>;
0x135e;:0;MOV	0x3ceb(%RIP),%RDI;
0x1365;:0;CALL	10b0 <.plt.sec@start>;
0x136a;:0;MOV	0x3ce7(%RIP),%RDI;
0x1371;:0;CALL	10b0 <.plt.sec@start>;
0x1376;:0;MOV	0x3ce3(%RIP),%RDI;
0x137d;:0;CALL	10b0 <.plt.sec@start>;
0x1382;:0;MOV	0x3ca7(%RIP),%RDI;
0x1389;:0;CALL	10b0 <.plt.sec@start>;
0x138e;:0;MOV	0x3ca3(%RIP),%RDI;
0x1395;:0;CALL	10b0 <.plt.sec@start>;
0x139a;:0;MOV	0x3c9f(%RIP),%RDI;
0x13a1;:0;CALL	10b0 <.plt.sec@start>;
0x13a6;:0;ADD	$0x18,%RSP;
0x13aa;:0;POP	%RBX;
0x13ab;:0;POP	%R10;
0x13ad;:0;POP	%R12;
0x13af;:0;POP	%R13;
0x13b1;:0;POP	%R14;
0x13b3;:0;XOR	%EAX,%EAX;
0x13b5;:0;POP	%RBP;
0x13b6;:0;RET;
0x13b7;:0;NOPW	(%RAX,%RAX,1);
0x13c0;:0;MOV	%R12,%RDI;(0) 
0x13c3;:0;CALL	10b0 <.plt.sec@start>;(0) 
0x13c8;:0;CALL	10c0 <.plt.sec@start+0x10>;(0) 
0x13cd;:0;VSUBSD	-0x40(%RBP),%XMM0,%XMM0;(0) 
0x13d2;:0;VADDSD	-0x38(%RBP),%XMM0,%XMM7;(0) 
0x13d7;:0;VMOVSD	%XMM7,-0x38(%RBP);(0) 
0x13dc;:0;JMP	129c <main+0x17c>;(0) 
0x13e1;:0;VXORPD	%XMM5,%XMM5,%XMM5;
0x13e5;:0;VMOVSD	%XMM5,-0x38(%RBP);
0x13ea;:0;JMP	12d3 <main+0x1b3>;
0x13ef;:0;NOP;
