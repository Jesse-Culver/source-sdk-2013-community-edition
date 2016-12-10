#include "cbase.h"
#include "VirtualMachine.h"


#define R_INDEX(x) (base+x)

// Register #x
#define R(x) (G.registry[R_INDEX(x)])

// TODO: Upvalues

// Constant #x
#define C(x) (S->currentFunction->function->constants[x])

// Register #x or Constant #x
#define RC(x) (IsC(x) ? C(x) : R(x))



void CVirtualMachine::Exexcute(VMState* S)
{

	// Current Instruction
	Instruction I;

	for (;;)
	{
		I = *(S->PC++);

		int base = 0;
		switch (GET_OP(*(S->PC)))
		{
			case (OP_MOVE) : {
				G.registry.Set( R_INDEX(GET_A(I)), R(GET_A(I)) );
			} continue;


			case (OP_LOAD) : {
				G.registry.Set( R_INDEX(GET_A(I)), C(GET_BC(I)) );
			} continue;



			case (OP_GET) : {
				Value& RCB = RC(GET_B(I));
				Value& RCC = RC(GET_C(I));

				if (RCB.type == VM_ARRAY) {
					if (RCC.type == VM_INT) {
						// A = array B[int C]
						G.registry.Set(R_INDEX(GET_A(I)), RCB.arr->Get(RCC.i));
					} else {
						// A = array B[!int C] - TODO
					}
				} else if (RCB.type == VM_OBJECT) {
					// A = object B[C] - TODO
				} else {
					// B is not an array or an object
				}
			} continue;


			case (OP_SET) : {
				Value& RA = R(GET_A(I));
				Value& RCB = RC(GET_B(I));
				Value& RCC = RC(GET_C(I));

				if (RA.type == VM_ARRAY) {
					if (RCB.type == VM_INT) {
						// array A[int B] = C
						RA.arr->Set(RCB.i, RCC);
					} else {
						// array A[!int B] = C - TODO
					}
				} else if (RA.type == VM_OBJECT) {
					// object A[B] = C - TODO
				} else {
					// A is not an array or an object - TODO
				}
			} continue;



			case (OP_DEL) : {
				int A = R_INDEX(GET_A(I));
				int B = GET_B(I);

				do {
					G.registry.Set(A++, Null);
				} while (B--);

			} continue;



			case (OP_JUMP) : {
				S->PC += GET_sBC(I);
			} continue;



			case (OP_RETURN) : {
				//int A = R_INDEX(GET_A(I));
				int B = GET_B(I);

				do {
					// TODO: return A++
				} while (B--);
			} break;

			default: { 

			} continue;

		}

		break;
	}

}