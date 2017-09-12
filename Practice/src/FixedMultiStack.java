public class FixedMultiStack{
		private int numOfStacks = 3;
		private int capacity;
		private int[] values;
		private int[] sp;
		
		public FixedMultiStack(int stackSize){
			capacity = stackSize;
			values = new int[numOfStacks*stackSize];
			sp = new int[numOfStacks];
		}
		public void push(int stackNum, int value){
			if(isFull(stackNum)){ 
				System.out.println("Stack "+stackNum+" is full!");
				return;
			}
			sp[stackNum]++;
			values[indexOfTop(stackNum)]=value;
		}
		
		public int pop(int stackNum){
			if(isEmpty(stackNum)){
				System.out.println("Stack "+stackNum+" is empty!");
				return -1;
			}
			int top = indexOfTop(stackNum);
			int value = values[top];
			values[top]=0;
			sp[stackNum]--;
			return value;
		}
		public int peek(int stackNum){
			if(isEmpty(stackNum)){
				System.out.println("Stack "+stackNum+" is empty!");
				return -1;
			}
			return values[indexOfTop(stackNum)];
		}
		public boolean isFull(int stackNum){
			if(sp[stackNum]==capacity){
				return true;
			}
			return false;
		}
		public boolean isEmpty(int stackNum){
			if(sp[stackNum]==0){
				return true;
			}
			return false;
		}
		private int indexOfTop(int stackNum){
			return (stackNum*capacity + (sp[stackNum]-1));
		}
	}