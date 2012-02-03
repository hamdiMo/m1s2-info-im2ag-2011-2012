(* open_graph "" ;; *)
#open "Graphics";;
(* #use "Graphics";; *)

type dot = float * float ;;
type vector = float * float ;;
type segment = dot * dot ;;
type courbe = segment list ;;

let rec (createCourbeFrom : dot list -> courbe) = function 
  | [] -> []
  | e::[] -> []
  | e1::e2::tail -> (e1, e2)::(createCourbeFrom (e2::tail))
;;

let rec (diviserSegment : segment -> segment list) = function 
  (p1, p2) -> 
    let (p1x, p1y) = p1 and (p2x, p2y) = p2 
    in let pInter = ((p1x+.p2x)/.2., (p1y+.p2y)/.2.)
       in [(p1, pInter); (pInter, p2)]
;;

let rec (diviserCourbe : courbe -> courbe) = function
  | [] -> []
  | h::t -> (diviserSegment h)@(diviserCourbe t)
;;

let (lisserCourbe : courbe -> courbe) = 
  function c0 -> 
    let c1 = diviserCourbe c0 
    in let rec (lisserCourbeRec : courbe -> courbe) = function
         | [] -> []
         | e::[] -> [e]
         | e1::e2::tail -> 
            let (p1, _) = e1 and (_, p2) = e2
            in (p1, p2)::(lisserCourbeRec tail)
       in match c1 with
          | [] -> []
          | e::[] -> c1
          | h1::t1 -> h1::(lisserCourbeRec t1)
;;

let dotSet = 
  let p1 = (0.0, 0.0)
  and p2 = (1.0, 10.0)
  and p3 = (2.0, -40.0)
  and p4 = (6.0, 20.0)
  in createCourbeFrom [p1;p2;p3;p4]
;;

let rec (lisserGlobal : courbe -> int -> courbe) = 
  fun c -> fun k -> 
    if (k > 0)
    then lisserCourbe (lisserGlobal c (k-1))
    else c
;;

dotSet;;

open_graph "800x500+40-30";;