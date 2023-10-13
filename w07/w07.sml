
(*
Create a file .sml that contains 4 functions (and nothing else):

      Write a function sq that returns the square of its parameter.
      Type: int -> int
         sq 5 -> 25

      Write a function sqsum that recursively finds the sums of the squares of a list
      Type: 'a list -> int
         sqsum [1,2,3] -> 14

Write a function cycle that takes a list L and an integer n and removes n elements
from the front of L and appends them to the end of L.
Type: 'a list * int -> 'a list
   cycle ([1,2,3,4,5], 2) -> [3,4,5,1,2]

Write a function semrev that is similar to cycle, but append n elements in reverse order
Type: 'a list * int -> 'a list
   semrev ([1,2,3,4,5], 2) -> [3,4,5,2,1]
*)

fun sq x = x * x;

fun sqsum(nil) = 0
|   sqsum(x::xs) = x * x + sqsum xs;

fun cycle([], _) = [] 
|   cycle(lst, 0) = lst
|   cycle(x::xs, n) = cycle(xs @ [x], n-1);

fun semrev([], _) = []
|   semrev(lst, 0) = lst
|   semrev(x::xs, n) = semrev(xs, n-1) @ [x];

