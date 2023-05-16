#include <iostream>

class RAM
{
	private:
		int* ram;
		int size;

	public:
		RAM(int size)
		{
			this->size = size;
			ram = new int[size];
		}

		~RAM()
		{
			delete[] ram;
		}

                void write(int address,int data)
		{
			if(address > 0 && address < size)
			{
				ram[address] = data;
			}
			else
			{
				std::cout<<"Invalid RAM address"<<std::endl;
			}
		}

		int read(int address)
		{
			if(address > 0 && address < size)
			{
				return ram[address];
			}
			else
			{
				std::cout<<"Invalid RAM address"<<std::endl;
				return -1;
			}
		}
};

class Register
{
	private:
		int* reg;
		int size;
	
	public:
		int counter;

		Register()
		{
			 counter = 0; 
		}
                

		Register(int size)
		{
			this->size = size;
			reg = new int[size];
		}

		~Register()
		{
			delete[] reg;
		}

		void write(int index,int data)
		{
			if(index > 0 && index < size)
			{
				reg[index] = data;
			}
			else
			{
				std::cout<<"Invalid register index"<<std::endl;
			}
		}

		int read(int index)
		{
			if(index > 0 && index < size)
			{
				return reg[index];
			}
			else
			{
				std::cout<< "Invalid register index"<<std::endl;
				return -1;
			}
		}

};
class ALU
{
	public:
		int calculate(int a,int b,char op)
		{
			switch(op)
			{
				case 1:
					return a + b;
				case 2:
					return a - b;
				case 3:
					return a * b;
				case 4:
					return a / b;
				case 5:
					return a & b;
				case 6:
					return a ^ b;
				case 7:
					return a | b;
				default:
					std::cout<<"Invalid operation"<<std::endl;
					return 0;
			}
		}
};


class Control_Unit
{
	private:
		RAM* ram;
		Register* reg;
		Register registers;
		ALU alu;
		
      	public:
		Control_Unit(RAM* ram,Register* reg)
		{
			this->ram = ram;
			this->reg = reg;
		}

		int fetch(int address)
		{
		  int instruction = ram->read(address);
		  registers.counter++;
		  return instruction;
		}

		void decode(int instruction)
		{
			reg->write(1,(instruction >> 12) & 0xF);
			reg->write(2,(instruction >> 8) & 0xF);
			reg->write(3,(instruction >> 4) & 0xF);
			reg->write(4,(instruction >> 0) & 0xF);
		}

		void execute()
		{
			reg->write(5,ram->read(reg->read(3)));
			reg->write(6,ram->read(reg->read(4)));
			ram->write(reg->read(2),alu.calculate(reg->read(5),reg->read(6),reg->read(1)));
		}

};

class CPU
{
	private:
		ALU alu;
		Control_Unit cu;
		RAM ram;
		Register reg;

	public:
		

};

int main()
{
	RAM ram(100);
	Register reg(6);
	Control_Unit cu(&ram,&reg);
	return 0;
}
