# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`da_cap`](#da_8h_1aef9885cf29028c16e56abd0e564d7eca)            | 
`define `[`da_len`](#da_8h_1a303efb267601c14b434ceb359bc11f78)            | 
`define `[`da_maxlen`](#da_8h_1ae7f65059a1c47bd7919050921e16a078)            | 
`define `[`da_ismutable`](#da_8h_1a973206acf4ca812a3d2961d029e3e750)            | 
`define `[`DA_DECL_SPEC`](#da__util_8h_1a7c3a5ba38c5b9c93fadbfb19ccda84b4)            | 
`define `[`DA_DEF_SPEC`](#da__util_8h_1a6a4ddb749c9a43e1889235dae6fb460d)            | 
`define `[`DA_DECL_HELPERS`](#da__util_8h_1acb04d2623ed07b0dadd050257a5dc1fa)            | 
`define `[`DA_DEF_HELPERS_EX`](#da__util_8h_1a19376109d47143288ccf1cc76ba28d70)            | 
`define `[`DA_DEF_HELPERS`](#da__util_8h_1a04d5e1644667d2867e4d7f86cf98803c)            | 
`public `[`da_t`](#structda__t)` * `[`da_new`](#da_8h_1ab4d2a41d6229872044ef300075ca0ba9)`(const `[`da_spec_t`](#structda__spec__t)` * sp)`            | Allocates and initializes a new da with the given spec and returns it. The returned value must be freed to avoid memory leaks.
`public void `[`da_init`](#da_8h_1ae2a0dfcaa9474511b518ca6a3dbf7376)`(`[`da_t`](#structda__t)` * da,const `[`da_spec_t`](#structda__spec__t)` * sp)`            | Initialize a previously allocated da with the given spec.
`public void `[`da_deinit`](#da_8h_1a4280ef3a8198e143b1131d070d2bbb29)`(`[`da_t`](#structda__t)` * da)`            | Deinitializes the given da. If `da`'s `spec`'s `free` pointer is set, it is called on all the members. `da`'s internal memory is then cleared.
`public void `[`da_free`](#da_8h_1a548a98544c3ab3c1d8219198c29afdda)`(`[`da_t`](#structda__t)` * da)`            | Deinitializes the given da then deallocates it.
`public `[`da_t`](#structda__t)` * `[`da_copy`](#da_8h_1aaf438ccd80b98365204e050372620225)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src)`            | Creates a copy of `src` and its elements to `dst` and returns `dst`. If `dst` if `NULL`, it will be allocated.
`public void * `[`da_get`](#da_8h_1a83d8d46b06601ebf35dc6b1d230f93e2)`(const `[`da_t`](#structda__t)` * da,int i)`            | Returns a pointer to the element at the given index `i`. If `i` if negative, it will return a element relative to the end of the array.
`public void `[`da_set`](#da_8h_1a1650aa3898df9d0f50aa6a3af16188e6)`(`[`da_t`](#structda__t)` * da,int i,const void * ep)`            | Sets the element at the given index `i`. If `i` is negative it will set the element relative to the end of the array.
`public void `[`da_setcap`](#da_8h_1a4929afb71a4c01ddd59ddac70eb2b3e0)`(`[`da_t`](#structda__t)` * da,int cap)`            | Sets the capacity of `da` to AT MOST the given `cap` and allocates enough internal memory to support that capacity. If the internal capacity is higher than `cap`, nothing happens.
`public void `[`da_append`](#da_8h_1a2513678a310f7d9256116b152dbc209a)`(`[`da_t`](#structda__t)` * da,const void * ep)`            | Pushes the given element to the end of `da`.
`public void `[`da_extend`](#da_8h_1a3963c8c8ae1fdce1c1451d6d608b5d74)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src)`            | Pushes the elements of `src` to the end of `dst`.
`public void * `[`da_pop`](#da_8h_1aaf94c51a1b06b2e474d2749179106022)`(`[`da_t`](#structda__t)` * da)`            | Pops and returns the last element of `da`.
`public void `[`da_clear`](#da_8h_1a60ad9c7c39fdad47cf42be485e728bad)`(`[`da_t`](#structda__t)` * da)`            | Clears the elements of `da`, but doesn't free its internal memory.
`public void `[`_da_assert`](#da_8h_1a7b4a9cea7d0d81c16a1fabd40af93224)`(int expr,const char * msg,...)`            | 
`public `[`da_t`](#structda__t)` `[`da_slice_val`](#da_8h_1a767ea7f1dbe20958e03deee20a1ccb7f)`(const `[`da_t`](#structda__t)` * src,int i,int j)`            | 
`public `[`da_t`](#structda__t)` * `[`da_slice`](#da_8h_1a8e69d6c4983bc16d136423bd9c492861)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src,int i,int j)`            | Sets the elements of `dst` to the elements of `src` in the range between `i` and `j`, then returns `dst`.
`public void `[`da_sort`](#da_8h_1a83b4b407759db15a68ff2afc4027469f)`(`[`da_t`](#structda__t)` * da,int(*)(const void *, const void *) cmp)`            | Sorts in place the elements of the array with the given `cmp` function.
`struct `[`da_spec_t`](#structda__spec__t) | 
`struct `[`da_t`](#structda__t) | 

## Members

#### `define `[`da_cap`](#da_8h_1aef9885cf29028c16e56abd0e564d7eca) 

#### `define `[`da_len`](#da_8h_1a303efb267601c14b434ceb359bc11f78) 

#### `define `[`da_maxlen`](#da_8h_1ae7f65059a1c47bd7919050921e16a078) 

#### `define `[`da_ismutable`](#da_8h_1a973206acf4ca812a3d2961d029e3e750) 

#### `define `[`DA_DECL_SPEC`](#da__util_8h_1a7c3a5ba38c5b9c93fadbfb19ccda84b4) 

#### `define `[`DA_DEF_SPEC`](#da__util_8h_1a6a4ddb749c9a43e1889235dae6fb460d) 

#### `define `[`DA_DECL_HELPERS`](#da__util_8h_1acb04d2623ed07b0dadd050257a5dc1fa) 

#### `define `[`DA_DEF_HELPERS_EX`](#da__util_8h_1a19376109d47143288ccf1cc76ba28d70) 

#### `define `[`DA_DEF_HELPERS`](#da__util_8h_1a04d5e1644667d2867e4d7f86cf98803c) 

#### `public `[`da_t`](#structda__t)` * `[`da_new`](#da_8h_1ab4d2a41d6229872044ef300075ca0ba9)`(const `[`da_spec_t`](#structda__spec__t)` * sp)` 

Allocates and initializes a new da with the given spec and returns it. The returned value must be freed to avoid memory leaks.

#### `public void `[`da_init`](#da_8h_1ae2a0dfcaa9474511b518ca6a3dbf7376)`(`[`da_t`](#structda__t)` * da,const `[`da_spec_t`](#structda__spec__t)` * sp)` 

Initialize a previously allocated da with the given spec.

#### `public void `[`da_deinit`](#da_8h_1a4280ef3a8198e143b1131d070d2bbb29)`(`[`da_t`](#structda__t)` * da)` 

Deinitializes the given da. If `da`'s `spec`'s `free` pointer is set, it is called on all the members. `da`'s internal memory is then cleared.

#### `public void `[`da_free`](#da_8h_1a548a98544c3ab3c1d8219198c29afdda)`(`[`da_t`](#structda__t)` * da)` 

Deinitializes the given da then deallocates it.

#### `public `[`da_t`](#structda__t)` * `[`da_copy`](#da_8h_1aaf438ccd80b98365204e050372620225)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src)` 

Creates a copy of `src` and its elements to `dst` and returns `dst`. If `dst` if `NULL`, it will be allocated.

#### `public void * `[`da_get`](#da_8h_1a83d8d46b06601ebf35dc6b1d230f93e2)`(const `[`da_t`](#structda__t)` * da,int i)` 

Returns a pointer to the element at the given index `i`. If `i` if negative, it will return a element relative to the end of the array.

#### `public void `[`da_set`](#da_8h_1a1650aa3898df9d0f50aa6a3af16188e6)`(`[`da_t`](#structda__t)` * da,int i,const void * ep)` 

Sets the element at the given index `i`. If `i` is negative it will set the element relative to the end of the array.

#### `public void `[`da_setcap`](#da_8h_1a4929afb71a4c01ddd59ddac70eb2b3e0)`(`[`da_t`](#structda__t)` * da,int cap)` 

Sets the capacity of `da` to AT MOST the given `cap` and allocates enough internal memory to support that capacity. If the internal capacity is higher than `cap`, nothing happens.

#### `public void `[`da_append`](#da_8h_1a2513678a310f7d9256116b152dbc209a)`(`[`da_t`](#structda__t)` * da,const void * ep)` 

Pushes the given element to the end of `da`.

#### `public void `[`da_extend`](#da_8h_1a3963c8c8ae1fdce1c1451d6d608b5d74)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src)` 

Pushes the elements of `src` to the end of `dst`.

#### `public void * `[`da_pop`](#da_8h_1aaf94c51a1b06b2e474d2749179106022)`(`[`da_t`](#structda__t)` * da)` 

Pops and returns the last element of `da`.

#### `public void `[`da_clear`](#da_8h_1a60ad9c7c39fdad47cf42be485e728bad)`(`[`da_t`](#structda__t)` * da)` 

Clears the elements of `da`, but doesn't free its internal memory.

#### `public void `[`_da_assert`](#da_8h_1a7b4a9cea7d0d81c16a1fabd40af93224)`(int expr,const char * msg,...)` 

#### `public `[`da_t`](#structda__t)` `[`da_slice_val`](#da_8h_1a767ea7f1dbe20958e03deee20a1ccb7f)`(const `[`da_t`](#structda__t)` * src,int i,int j)` 

#### `public `[`da_t`](#structda__t)` * `[`da_slice`](#da_8h_1a8e69d6c4983bc16d136423bd9c492861)`(`[`da_t`](#structda__t)` * dst,const `[`da_t`](#structda__t)` * src,int i,int j)` 

Sets the elements of `dst` to the elements of `src` in the range between `i` and `j`, then returns `dst`.

`dst` is assumed to be uninitialized. If `dst` is `NULL`, it will be allocated.

NOTE: `dst` will contain the same internal memory of as `src`. The elements will not be copied. Mutating the elements of one will mutate the elements of the other. `dst` itself cannot be appended to or extended.

#### `public void `[`da_sort`](#da_8h_1a83b4b407759db15a68ff2afc4027469f)`(`[`da_t`](#structda__t)` * da,int(*)(const void *, const void *) cmp)` 

Sorts in place the elements of the array with the given `cmp` function.

# struct `da_spec_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public size_t `[`size`](#structda__spec__t_1a27302589ecc07aafc57e78ce06e6fe71) | 
`public `[`da_init_func_t`](#da_8h_1aeb9ffe97105529004ae5795eac0c8d97)` * `[`init`](#structda__spec__t_1a771aa7be8acdd60e70ca7b33ed7c15ca) | 
`public `[`da_copy_func_t`](#da_8h_1a41114256ec2e29681ded73c370895177)` * `[`copy`](#structda__spec__t_1a14c7d65ccdf57f84c652351767b64275) | 
`public `[`da_free_func_t`](#da_8h_1a62cdc9fe47fa1cb2f0a8d4b8dc12b780)` * `[`free`](#structda__spec__t_1a6555f056601e7e85ed0a928eb1b654a2) | 

## Members

#### `public size_t `[`size`](#structda__spec__t_1a27302589ecc07aafc57e78ce06e6fe71) 

#### `public `[`da_init_func_t`](#da_8h_1aeb9ffe97105529004ae5795eac0c8d97)` * `[`init`](#structda__spec__t_1a771aa7be8acdd60e70ca7b33ed7c15ca) 

#### `public `[`da_copy_func_t`](#da_8h_1a41114256ec2e29681ded73c370895177)` * `[`copy`](#structda__spec__t_1a14c7d65ccdf57f84c652351767b64275) 

#### `public `[`da_free_func_t`](#da_8h_1a62cdc9fe47fa1cb2f0a8d4b8dc12b780)` * `[`free`](#structda__spec__t_1a6555f056601e7e85ed0a928eb1b654a2) 

# struct `da_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const `[`da_spec_t`](#structda__spec__t)` * `[`spec`](#structda__t_1affc19c32a1c54595e6d08e2a127152ed) | 
`public void * `[`data`](#structda__t_1a0483f3f880cb754aea1b5a3b33b46892) | 
`public int `[`len`](#structda__t_1aa5c08b20aab02a363b07369706b7e0c8) | 
`public int `[`cap`](#structda__t_1a7da30976d88f9d293d12f82b0c2fb111) | 

## Members

#### `public const `[`da_spec_t`](#structda__spec__t)` * `[`spec`](#structda__t_1affc19c32a1c54595e6d08e2a127152ed) 

#### `public void * `[`data`](#structda__t_1a0483f3f880cb754aea1b5a3b33b46892) 

#### `public int `[`len`](#structda__t_1aa5c08b20aab02a363b07369706b7e0c8) 

#### `public int `[`cap`](#structda__t_1a7da30976d88f9d293d12f82b0c2fb111) 

Generated by [Moxygen](https://sourcey.com/moxygen)