type id = string

type binop =
      Plus
    | Minus
    | Times
    | Div

type stmt =
      CompoundStm of stmt * stmt
    | AssignStm of id * expr
    | PrintStm of expr list
and expr =
      IdExp of id
    | NumExp of int
    | OpExp of expr * binop * expr
    | EseqExp of stmt * expr


let prog = 
 CompoundStm(
        AssignStm("a",
                  OpExp(NumExp 5, Plus, NumExp 3)),
        CompoundStm(
                AssignStm("b",
                      EseqExp(
                              PrintStm[IdExp"a";OpExp(IdExp"a", Minus,NumExp 1)],
                              OpExp(NumExp 10, Times, IdExp"a"))),
                      PrintStm[IdExp "b"]))

let list_max = function
      [] -> invalid_arg "empty list"
    | x::xs -> List.fold_left max x xs

let rec maxargs (stm:stmt) : int =
    let rec maxargs_e (exp:expr) : int =
        match exp with
            | EseqExp (s, e) ->
                let res1 = maxargs s in
                let res2 = maxargs_e e in
                    if res1 > res2 then res1 else res2
            | _ -> 0
    in
    match stm with
        | PrintStm pl ->
            let current = List.length pl in
            let deeper  = list_max (List.map maxargs_e pl) in
                if current > deeper then current else deeper
        | AssignStm (_, e) -> maxargs_e e
        | CompoundStm (s1, s2) ->
            let res1 = maxargs s1 in
            let res2 = maxargs s2 in
                if res1 > res2 then res1 else res2

(* environment variables for interpreter *)
type table = (id * int) list

let update tb id integer = (id, integer) :: tb

let rec lookup (tb:table) (id:id) : int =
    match tb with
        | [] -> 0
        | ((id', v) :: tb') ->
            if id = id' then v else lookup tb' id

let print_op (b:binop) : unit = 
    match b with 
          Plus  -> print_string "+"
        | Minus -> print_string "-"
        | Times -> print_string "*"
        | Div   -> print_string "/"

let rec print_expr (e:expr) : unit =
    match e with
          IdExp id -> print_string id
        | NumExp n -> print_string (string_of_int n)
        | OpExp (e1, b, e2) -> (print_expr e1; print_op b; print_expr e2)
        | EseqExp (_, e1)   -> print_expr e1


let rec interpStm (s:stmt) (tb:table) : table =
    let rec interpExp (e:expr) (tb:table) : int * table =
        match e with
              IdExp id -> ((lookup tb id), tb)
            | NumExp n -> (n, tb)
            | OpExp (e1, b, e2) ->
                let (v1, tb1) = interpExp e1 tb  in
                let (v2, tb2) = interpExp e2 tb1 in
                        (match b with
                              Plus  -> ((v1 + v2), tb2)
                            | Minus -> ((v1 - v2), tb2)
                            | Times -> ((v1 * v2), tb2)
                            | Div   -> ((v1 / v2), tb2))
            | EseqExp (s, e) -> interpExp e (interpStm s tb)
    in
    match s with
          CompoundStm (s1, s2) -> interpStm s2 (interpStm s1 tb)
        | AssignStm (id, e1)   ->
            let (v, tb1) = interpExp e1 tb in
                update tb1 id v
        | PrintStm elist ->
            match elist with
                  []     -> tb
                | (h::t) ->
                    let (_, tb1) = (print_expr h; interpExp h tb) in
                        interpStm (PrintStm t)  tb1
