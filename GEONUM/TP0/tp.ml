(* http://imagine.inrialpes.fr/people/Brouet.Remi/Teaching/teaching.html *)

(* Programme de tracé de courbes de bézier *)

(* Pour la compilation en executable : *)
(* ocamlc graphics.cma tp.ml -o bezier *)

(* load "graphics.cma";; *)
open Graphics ;;

type dot = float * float ;;


let run = fun () ->
  let n = read_int (print_string "Combien de points possede la courbe ? ")
  and m = read_int (print_string "Combien de points de control par segment ? ")
  in

  Graphics.open_graph " 512x512";

  let (drawDot : dot -> unit) = fun (x, y) ->
    let intX = int_of_float x
    and intY = int_of_float y in
    Graphics.plot intX intY;
    Graphics.draw_circle intX intY 5
  in

  let rec (drawDots : dot list -> unit) = function
    | [] -> ()
    | e::t -> drawDot e; drawDots t
  in

  let rec (drawCurve : dot list -> unit) = function
    | [] -> ()
    | (x, y)::[] -> Graphics.plot (int_of_float x) (int_of_float y)
    | (x0, y0)::(x1, y1)::t -> 
      Graphics.moveto (int_of_float x0) (int_of_float y0);
      Graphics.lineto (int_of_float x1) (int_of_float y1);
      drawCurve ((x1,y1)::t)
  in 

  let curveInit =
    let rec (waitDots : int -> dot list) = fun n ->
      if (n > 0) 
      then
        let dots = (waitDots (n-1)) in
        drawCurve dots;
        let e = Graphics.wait_next_event [Graphics.Button_down] in 
        let dot = ((float_of_int e.Graphics.mouse_x), (float_of_int e.Graphics.mouse_y)) in
        drawDot dot;
        dot::dots
      else []
    in waitDots n
  in 
  

  let (controlDotFromSegment : float -> dot -> dot -> dot) = 
    fun k -> fun (aX, aY) -> fun (bX, bY) -> ((1.-.k)*.aX+.k*.bX, (1.-.k)*.aY+.k*.bY)
  in

  let rec (controlDotListFromCurve : float -> dot list -> dot list) =
    fun k -> function
      | [] -> []
      | h::[] -> []
      | p1::p2::tail -> (controlDotFromSegment k p1 p2)::(controlDotListFromCurve k (p2::tail))
  in

  let rec (controlDotFromCurve : float -> dot list -> dot) =
    fun k -> function 
      | [] -> failwith "controlDotFromCurve"
      | e::[] -> e
      | l -> 
        Graphics.set_color (Graphics.rgb 0 0 255); drawCurve l;
        let dot = controlDotFromCurve k (controlDotListFromCurve k l) in
        Graphics.set_color (Graphics.rgb 255 0 0); drawDot dot;
        dot
  in

  let (smoothingCurveFromCurve : int -> dot list -> dot list) = 
    fun n -> 
      let (k : float) = 1. /. (float_of_int (n))
      in let rec (smoothingCurveFromCurveRec : int -> dot list -> dot list) =
           fun it -> fun c -> 
             let dots = 
               if (it <= n)
               then (controlDotFromCurve ((float_of_int it)*.k) c)::(smoothingCurveFromCurveRec (it+1) c)
               else []
             in 
             Graphics.set_color (Graphics.rgb 0 0 0); drawCurve curveInit;
             Graphics.set_color (Graphics.rgb 255 0 0); drawCurve dots;

             Graphics.synchronize ();
             Graphics.clear_graph ();
             dots
         in smoothingCurveFromCurveRec 0
  in

  drawCurve curveInit;
  Graphics.auto_synchronize false;
  Graphics.wait_next_event [Graphics.Button_down];
  let c1 = smoothingCurveFromCurve m curveInit in
  Graphics.set_color (Graphics.rgb 255 0 0);
  drawCurve c1;
  
  let rec waitSpaceEvent = fun () ->
    let e = Graphics.wait_next_event [Graphics.Key_pressed]
    in 
    if (e.Graphics.keypressed)
    then ()
    else waitSpaceEvent ()
  in waitSpaceEvent ();
  
  Graphics.close_graph ()
;;

run () ;;
