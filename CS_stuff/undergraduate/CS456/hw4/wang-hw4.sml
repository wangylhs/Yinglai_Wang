(* Yinglai Wang hw4 *)
 
exception Mismatch;
exception Domain;
exception Empty;
exception NotFound;

(* 1:Pattern Matching *)
(* a *)
fun fib 0 = 0
  | fib 1 = 1
  | fib n = fib(n-1)+fib(n-2);
 
(* b *)
(* firstVowel *)
fun firstVowel (#"a"::_) = true
  | firstVowel (#"e"::_) = true
  | firstVowel (#"i"::_) = true
  | firstVowel (#"o"::_) = true
  | firstVowel (#"u"::_) = true
  | firstVowel _ = false;

(* c *)
(* null *)
fun null [] = true
  | null _ = false;

(* 2:Lists *)
(* a *)
fun rev nil = nil
  | rev x = foldl op:: nil x;

(* b *)
fun minlist (x::xs) = foldl (fn(a, b)=> if a<=b then a else b) x xs
  | minlist [] = raise Empty;

(* c *)
fun foldl f x [] = x
  | foldl f x (y::ys) = foldl f (f(y, x)) ys;

fun foldr f x [] = x
  | foldr f x (y::ys) = f(y, (foldr f x ys));

(* d&e *)

fun pairfoldr f z ([], []) = z
  | pairfoldr f a (x::xs, y::ys) = f(x,y, (pairfoldr f a (xs, ys)))
  | pairfoldr f z _ = raise Mismatch;

fun zip (x,y) = pairfoldr (fn (x, y, z) => ((x, y)::z)) [] (x,y);


(* f *)
fun unzip [] = ([],[])
  | unzip ((x1,y1)::l) =
                    let val (xs,ys) = unzip l in (x1::xs,y1::ys) end;

(* g *)
fun flatten [] = []
  | flatten (x::xs) = x @ flatten xs;

(* 3:Exceptions *)
(* a *)
fun nth x (y::[]) = if x=0 then y else raise Domain
  | nth x (y::ys) = if x<0 then raise Domain 
                      else if x=0 then y else nth (x-1) ys
  | nth x [] = raise Empty;

(* b *)
(* i *)
type 'a env = (string * 'a) list

val emptyEnv = [];

fun lookup (x:string, []) = raise NotFound
  | lookup (x:string, ((y, z)::zs)) = if x=y then z
                                      else lookup (x, zs);
fun bindVar (x:string, y, env) =
(fn z:string => if z=x then y else lookup (x, env));

(* ii *)
type 'a env = string -> 'a

fun emptyEnv(x:string) = raise NotFound;

fun bindVar (x:string, y, env) = (x, y)::env;

fun lookup(x:string, env2) = env2 x;


(* iii *)
fun isBound (x:string, env) = let val y = lookup (x, env) in true end
handle NotFound => false;

(* iv *)
fun extendEnv (xs, ys, env) =
let fun pairfold f z ([], []) = z
      | pairfold f z (x::xs, y::ys) = f (x, y, pairfold f z (xs, ys))
      | pairfold _ _ _ = raise Match;
in
pairfold bindVar env (xs, ys) end;




(* 4:Algebraic *)
(* a *)
datatype 'a tree = NODE of 'a tree * 'a * 'a tree | LEAF

fun insert cmp =
let fun ins (x, LEAF) = NODE (LEAF, x, LEAF)
| ins (x, NODE (left, y, right)) =
(case cmp (x, y)
of LESS    => NODE (ins (x, left), y, right)
| GREATER => NODE (left, y, ins (x, right))
| EQUAL   => NODE (left, x, right))
in ins
end

datatype 'a set = SET of ('a * 'a -> order) * 'a tree
fun nullset cmp = SET (cmp, LEAF)

fun addelt (a, (SET (cmp, xs))) = SET (cmp, ((insert cmp) (a, xs)))

fun orderhelper (NODE(l,m,r)) = orderhelper l @ [m] @ orderhelper r | orderhelper LEAF = []

fun treeFoldr f x xs = foldr f x (orderhelper (xs))

fun setFold f (x:'a) ((SET(cmp, xs)):'b set) = treeFoldr f x xs;



(* b *)
datatype 'a seq = EMPTY
                | SINGLETON of ('a)
                | SEQ of ('a seq * 'a seq);

fun scons (x, sq) = SEQ(SINGLETON(x) , sq); 

fun ssnoc (x, sq) = SEQ(sq, SINGLETON(x));

fun sappend (sq1, sq2) = (SEQ(sq1, sq2));

fun listOfSeq (EMPTY) = []
  | listOfSeq (SINGLETON(x)) = [x]
  | listOfSeq (SEQ(sq1, sq2)) = listOfSeq(sq1)@listOfSeq(sq2);

fun seqOfList (x) = foldr scons EMPTY x;

(* 5:Linked list *)

type 'a flist = ('a list * 'a * 'a list);

fun singletonOf (x) = ([], x, []);

fun atFinger(xs, y, zs) = y;

fun fingerRight(xs, y, []) = raise Subscript
  | fingerRight(xs, y, z::zs) = (y::xs, z, zs);

fun fingerLeft([], y, zs) = raise Subscript 
  | fingerLeft(x::xs, y, zs) = (xs, x, y::zs);

fun insertLeft(a, (xs, y, zs)) = (a::xs, y, zs);

fun insertRight(a, (xs, y, zs)) = (xs, y, a::zs);

fun deleteLeft([], y, zs) = raise Subscript
  | deleteLeft(x::xs, y, zs) = (xs, y, zs);

fun deleteRight(xs, y, []) = raise Subscript
  | deleteRight(xs, y, z::zs) = (xs, y, zs);

fun ffoldl (f, a, ([], y, [])) = foldl f a [y]
  | ffoldl (f, a, (xs, y, [])) = foldl f a (rev(y::xs))
  | ffoldl (f, a, ([], y, zs)) = foldl f a (y::zs)
  | ffoldl (f, a, (x::xs, y, zs)) = foldl f a (rev(x::xs) @ (y::zs));

fun ffoldr (f, a, ([], y, [])) = foldr f a [y]
  | ffoldr (f, a, (xs, y, [])) = foldr f a (rev(y::xs))
  | ffoldr (f, a, ([], y, zs)) = foldr f a (y::zs)
  | ffoldr (f, a, (x::xs, y, zs)) = foldr f a (rev(x::xs) @ (y::zs));
