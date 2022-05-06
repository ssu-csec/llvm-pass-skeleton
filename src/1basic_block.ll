; ModuleID = '../../basic_block.c'
source_filename = "../../basic_block.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @basic_block(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 1, i32* %6, align 4
  store i32 2, i32* %7, align 4
  %9 = load i32, i32 1, align 4
  %10 = load i32, i32* %7, align 4
  %11 = icmp eq i32 %9, %10
  br i1 %11, label %12, label %16

12:                                               ; preds = %2
  %13 = load i32, i32* %4, align 4
  %14 = load i32, i32* %5, align 4
  %15 = mul nsw i32 %13, %14
  store i32 %15, i32* %8, align 4
  br label %29

16:                                               ; preds = %2
  %17 = load i32, i32* %6, align 4
  %18 = load i32, i32* %7, align 4
  %19 = icmp sgt i32 %17, %18
  br i1 %19, label %20, label %24

20:                                               ; preds = %16
  %21 = load i32, i32* %5, align 4
  %22 = load i32, i32* %5, align 4
  %23 = mul nsw i32 %21, %22
  store i32 %23, i32* %8, align 4
  br label %28

24:                                               ; preds = %16
  %25 = load i32, i32* %6, align 4
  %26 = load i32, i32* %7, align 4
  %27 = add nsw i32 %25, %26
  store i32 %27, i32* %8, align 4
  br label %28

28:                                               ; preds = %24, %20
  br label %29

29:                                               ; preds = %28, %12
  %30 = load i32, i32* %8, align 4
  %31 = icmp sgt i32 %30, 100
  br i1 %31, label %32, label %33

32:                                               ; preds = %29
  store i32 0, i32* %3, align 4
  br label %35

33:                                               ; preds = %29
  %34 = load i32, i32* %8, align 4
  store i32 %34, i32* %3, align 4
  br label %35

35:                                               ; preds = %33, %32
  %36 = load i32, i32* %3, align 4
  ret i32 %36
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = call i32 @basic_block(i32 1, i32 2)
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"Ubuntu clang version 13.0.1-++20220120110924+75e33f71c2da-1~exp1~20220120231001.58"}
