
public class PseudoRandom {
	public int calculateNext(int s){
		s ^= s << 2;
		s ^= s >>> 21;
		s ^= (s << 7);
		return s;
	}
}
