address;source_location;insn;indent
0x1a80;:0;ENDBR64;
0x1a84;:0;VMOVSD	(%RDI),%XMM0;
0x1a88;:0;VMOVSD	0x18(%RDI),%XMM2;
0x1a8d;:0;MOV	0x35dc(%RIP),%RDX;
0x1a94;:0;VSUBSD	%XMM2,%XMM0,%XMM3;
0x1a98;:0;MOVSXD	%ESI,%RAX;
0x1a9b;:0;VMOVSD	(%RDX,%RAX,8),%XMM1;
0x1aa0;:0;VCOMISD	%XMM3,%XMM1;
0x1aa4;:0;JBE	1bc0 <insertParticle+0x140>;
0x1aaa;:0;PUSH	%R13;
0x1aac;:0;PUSH	%R12;
0x1aae;:0;MOV	%RAX,%R12;
0x1ab1;:0;PUSH	%RBP;
0x1ab2;:0;LEA	(,%RAX,8),%RBP;
0x1aba;:0;PUSH	%RBX;
0x1abb;:0;MOV	%RDI,%RBX;
0x1abe;:0;SUB	$0x8,%RSP;
0x1ac2;:0;MOV	0x35af(%RIP),%RDX;
0x1ac9;:0;VMOVSD	0x8(%RDI),%XMM3;
0x1ace;:0;VMOVSD	(%RDX,%RAX,8),%XMM5;
0x1ad3;:0;MOV	0x35a6(%RIP),%RDX;
0x1ada;:0;VMOVSD	0x10(%RDI),%XMM6;
0x1adf;:0;VMOVSD	(%RDX,%RAX,8),%XMM8;
0x1ae4;:0;VMOVSD	0x20(%RDI),%XMM4;
0x1ae9;:0;VMOVSD	0x28(%RDI),%XMM7;
0x1aee;:0;VADDSD	%XMM2,%XMM0,%XMM0;(5) 
0x1af2;:0;VCOMISD	%XMM1,%XMM0;(5) 
0x1af6;:0;JAE	1b08 <insertParticle+0x88>;(5) 
0x1af8;:0;ADD	$0x8,%RSP;
0x1afc;:0;POP	%RBX;
0x1afd;:0;POP	%RBP;
0x1afe;:0;POP	%R12;
0x1b00;:0;POP	%R13;
0x1b02;:0;RET;
0x1b03;:0;NOPL	(%RAX,%RAX,1);
0x1b08;:0;VSUBSD	%XMM4,%XMM3,%XMM0;(5) 
0x1b0c;:0;VCOMISD	%XMM0,%XMM5;(5) 
0x1b10;:0;JBE	1af8 <insertParticle+0x78>;(5) 
0x1b12;:0;VADDSD	%XMM4,%XMM3,%XMM3;(5) 
0x1b16;:0;VCOMISD	%XMM5,%XMM3;(5) 
0x1b1a;:0;JB	1af8 <insertParticle+0x78>;(5) 
0x1b1c;:0;VSUBSD	%XMM7,%XMM6,%XMM0;(5) 
0x1b20;:0;VCOMISD	%XMM0,%XMM8;(5) 
0x1b24;:0;JBE	1af8 <insertParticle+0x78>;(5) 
0x1b26;:0;VADDSD	%XMM7,%XMM6,%XMM6;(5) 
0x1b2a;:0;VCOMISD	%XMM8,%XMM6;(5) 
0x1b2f;:0;JB	1af8 <insertParticle+0x78>;(5) 
0x1b31;:0;MOV	0x30(%RBX),%EAX;(5) 
0x1b34;:0;INC	%EAX;(5) 
0x1b36;:0;CMPB	$0,0x38(%RBX);(5) 
0x1b3a;:0;MOV	%EAX,0x30(%RBX);(5) 
0x1b3d;:0;JNE	1bc8 <insertParticle+0x148>;(5) 
0x1b43;:0;CMP	$0x1,%EAX;(5) 
0x1b46;:0;JE	1c18 <insertParticle+0x198>;(5) 
0x1b4c;:0;MOV	0x34(%RBX),%R13D;(5) 
0x1b50;:0;MOV	%RBX,%RDI;(5) 
0x1b53;:0;CALL	1850 <subdivide>;(5) 
0x1b58;:0;MOV	%R13D,%ESI;(5) 
0x1b5b;:0;MOV	%RBX,%RDI;(5) 
0x1b5e;:0;CALL	1a80 <insertParticle>;(5) 
0x1b63;:0;VMOVSD	(%RBX),%XMM0;(5) 
0x1b67;:0;VMOVSD	0x18(%RBX),%XMM2;(5) 
0x1b6c;:0;MOV	0x34fd(%RIP),%RAX;(5) 
0x1b73;:0;VSUBSD	%XMM2,%XMM0,%XMM3;(5) 
0x1b77;:0;VMOVSD	(%RAX,%RBP,1),%XMM1;(5) 
0x1b7c;:0;SUBL	$0x2,0x30(%RBX);(5) 
0x1b80;:0;VCOMISD	%XMM3,%XMM1;(5) 
0x1b84;:0;JBE	1af8 <insertParticle+0x78>;(5) 
0x1b8a;:0;MOV	0x34e7(%RIP),%RAX;(5) 
0x1b91;:0;VMOVSD	0x8(%RBX),%XMM3;(5) 
0x1b96;:0;VMOVSD	(%RAX,%RBP,1),%XMM5;(5) 
0x1b9b;:0;MOV	0x34de(%RIP),%RAX;(5) 
0x1ba2;:0;VMOVSD	0x10(%RBX),%XMM6;(5) 
0x1ba7;:0;VMOVSD	(%RAX,%RBP,1),%XMM8;(5) 
0x1bac;:0;VMOVSD	0x20(%RBX),%XMM4;(5) 
0x1bb1;:0;VMOVSD	0x28(%RBX),%XMM7;(5) 
0x1bb6;:0;JMP	1aee <insertParticle+0x6e>;(5) 
0x1bbb;:0;NOPL	(%RAX,%RAX,1);
0x1bc0;:0;RET;
0x1bc1;:0;NOPL	(%RAX);
0x1bc8;:0;LEA	0x40(%RBX),%RBP;
0x1bcc;:0;SUB	$-0x80,%RBX;
0x1bd0;:0;MOV	(%RBP),%RDI;(4) 
0x1bd4;:0;MOV	%R12D,%ESI;(4) 
0x1bd7;:0;CALL	1a80 <insertParticle>;(4) 
0x1bdc;:0;MOV	0x8(%RBP),%RDI;(4) 
0x1be0;:0;MOV	%R12D,%ESI;(4) 
0x1be3;:0;CALL	1a80 <insertParticle>;(4) 
0x1be8;:0;MOV	0x10(%RBP),%RDI;(4) 
0x1bec;:0;MOV	%R12D,%ESI;(4) 
0x1bef;:0;CALL	1a80 <insertParticle>;(4) 
0x1bf4;:0;MOV	0x18(%RBP),%RDI;(4) 
0x1bf8;:0;MOV	%R12D,%ESI;(4) 
0x1bfb;:0;ADD	$0x20,%RBP;(4) 
0x1bff;:0;CALL	1a80 <insertParticle>;(4) 
0x1c04;:0;CMP	%RBX,%RBP;(4) 
0x1c07;:0;JNE	1bd0 <insertParticle+0x150>;(4) 
0x1c09;:0;ADD	$0x8,%RSP;
0x1c0d;:0;POP	%RBX;
0x1c0e;:0;POP	%RBP;
0x1c0f;:0;POP	%R12;
0x1c11;:0;POP	%R13;
0x1c13;:0;RET;
0x1c14;:0;NOPL	(%RAX);
0x1c18;:0;MOV	%R12D,0x34(%RBX);
0x1c1c;:0;ADD	$0x8,%RSP;
0x1c20;:0;POP	%RBX;
0x1c21;:0;POP	%RBP;
0x1c22;:0;POP	%R12;
0x1c24;:0;POP	%R13;
0x1c26;:0;RET;
0x1c27;:0;NOPW	(%RAX,%RAX,1);
