Following is a good suggestion [https://aturon.github.io/features/let.html]

> When consuming a struct or tuple via a let, bind all of the fields
> rather than using `..` to elide the ones you don't need. The benefit
> is that when fields are added, the compiler will pinpoint all of the
> places where that type of value was consumed, which will often need
> to be adjusted to take the new field properly into account.

Why give the eliding feature and then suggesting not to use it ?
