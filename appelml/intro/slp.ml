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
