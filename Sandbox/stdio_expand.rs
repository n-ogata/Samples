#![feature(prelude_import)]
#![no_std]
#[prelude_import]
use ::std::prelude::v1::*;
#[macro_use]
extern crate std;
macro_rules! input {
    (source = $ s : expr, $ ($ r : tt) *) =>
    {
        let mut iter = $ s . split_whitespace () ; input_inner !
        { iter, $ ($ r) * }
    } ; ($ ($ r : tt) *) =>
    {
        let s =
        {
            use std :: io :: Read ; let mut s = String :: new () ; std :: io
            :: stdin () . read_to_string (& mut s) . unwrap () ; s
        } ; let mut iter = s . split_whitespace () ; input_inner !
        { iter, $ ($ r) * }
    } ;
}

macro_rules! input_inner {
    ($ iter : expr) => { } ; ($ iter : expr,) => { } ;
    ($ iter : expr, $ var : ident : $ t : tt $ ($ r : tt) *) =>
    {
        let $ var = read_value ! ($ iter, $ t) ; input_inner !
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
    let s =
        {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
    let mut iter = s.split_whitespace();
    let n = iter.next().unwrap().parse::<u64>().expect("Parse error");
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
