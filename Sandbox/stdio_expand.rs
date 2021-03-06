#![feature(prelude_import)]
#![no_std]
#[prelude_import]
use ::std::prelude::v1::*;
#[macro_use]
extern crate std;
#[allow(dead_code)]
fn read_line(n: usize) -> String {
    let mut ss = String::new();
    for _i in 0..n {
        let mut s = String::new();
        std::io::stdin().read_line(&mut s).unwrap();
        ss.push_str(&s);
    }
    ss
}

macro_rules! parse {
    ($ s : expr => $ ($ r : tt) *) =>
    {
        let s = $ s ; let mut iter = s . split_whitespace () ; input_inner !
        { iter, $ ($ r) * }
    } ; ($ ($ r : tt) *) =>
    {
        use std :: io :: Read ; let mut s = String :: new () ; std :: io ::
        stdin () . read_to_string (& mut s) . unwrap () ; parse !
        { s => $ ($ r) * }
    } ;
}

macro_rules! input_inner {
    ($ iter : expr) => { } ; ($ iter : expr,) => { } ;
    ($ iter : expr, $ var : ident : $ t : tt $ ($ r : tt) *) =>
    {
        let $ var = read_value ! ($ iter, $ t) ; input_inner !
        { $ iter $ ($ r) * }
    } ; ($ iter : expr, mut $ var : ident : $ t : tt $ ($ r : tt) *) =>
    {
        let mut $ var = read_value ! ($ iter, $ t) ; input_inner !
        { $ iter $ ($ r) * }
    } ;
}

macro_rules! read_value {
    ($ iter : expr, ($ ($ t : tt), *)) =>
    { ($ (read_value ! ($ iter, $ t)), *) } ;
    ($ iter : expr, [$ t : tt ; $ len : expr]) =>
    {
        (0 .. $ len) . map (| _ | read_value ! ($ iter, $ t)) . collect :: <
        Vec < _ >> ()
    } ; ($ iter : expr, chars) =>
    {
        read_value ! ($ iter, String) . chars () . collect :: < Vec < char >>
        ()
    } ; ($ iter : expr, usize1) => { read_value ! ($ iter, usize) - 1 } ;
    ($ iter : expr, $ t : ty) =>
    {
        $ iter . next () . unwrap () . parse :: < $ t > () . expect
        ("Parse error")
    } ;
}

fn main() {
    // 複数回読み込む
    {
        let s = read_line(2);
        let mut iter = s.split_whitespace();
        let n = iter.next().unwrap().parse::<usize>().expect("Parse error");
        let v =
            (0..n).map(|_|
                           iter.next().unwrap().parse::<i32>().expect("Parse error")).collect::<Vec<_>>();
        // 一気に読み込む
        {
            ::std::io::_print(::core::fmt::Arguments::new_v1(&["", "\n"],
                                                             &match (&v,) {
                                                                  (arg0,) =>
                                                                  [::core::fmt::ArgumentV1::new(arg0,
                                                                                                ::core::fmt::Debug::fmt)],
                                                              }));
        };
    }
    {
        let s = read_line(2);
        let mut iter = s.split_whitespace();
        let n = iter.next().unwrap().parse::<usize>().expect("Parse error");
        let mut v =
            (0..n).map(|_|
                           iter.next().unwrap().parse::<i32>().expect("Parse error")).collect::<Vec<_>>();
        v[0] = 1;
        {
            ::std::io::_print(::core::fmt::Arguments::new_v1(&["", "\n"],
                                                             &match (&v,) {
                                                                  (arg0,) =>
                                                                  [::core::fmt::ArgumentV1::new(arg0,
                                                                                                ::core::fmt::Debug::fmt)],
                                                              }));
        };
    }
    {
        use std::io::Read;
        let mut s = String::new();
        std::io::stdin().read_to_string(&mut s).unwrap();
        let s = s;
        let mut iter = s.split_whitespace();
        let n = iter.next().unwrap().parse::<usize>().expect("Parse error");
        let v =
            (0..n).map(|_|
                           iter.next().unwrap().parse::<i32>().expect("Parse error")).collect::<Vec<_>>();
        {
            ::std::io::_print(::core::fmt::Arguments::new_v1(&["", "\n"],
                                                             &match (&v,) {
                                                                  (arg0,) =>
                                                                  [::core::fmt::ArgumentV1::new(arg0,
                                                                                                ::core::fmt::Debug::fmt)],
                                                              }));
        };
    }
}
