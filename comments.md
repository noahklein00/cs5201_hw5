-2 Your code has warnings - you should not be comparing signed and unsigned expressions

-3 You should not hardcode the template type for your invert function -
it would preclude a user from inverting a matrix of 'double's, for example

-10 Memory leak if matrix initializer_list ctor has rows of different size - recall that
"all fully constructed objects are deallocated"

-3 Kalman polymorphism doesn't make sense - its override of the single-arg op()
shouldn't just act as a dummy filter.  The interface isn't really used

Be more specific with your template type preconds - if you require op* for a type,
you need to specify its arity and its required return type

-3 The .5 in your model calculation is not needed - thus the numerical integration is incorrect
(angle just the time derivative of angular velocity, so the formula you used to calculate
  angular velocity given angular acceleration would have sufficed)

-3 Combination filter should have been a class (like all the other filters)

-2 Non-template code (your lander class) belongs in a cpp (compiled file, not header/template impl)

-2 Your filter op() is missing `const` on its argument 

Your score is:
72
