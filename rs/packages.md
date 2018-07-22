External packages
-----------------

```
ar                      {      stage0{         compiler}
arrayvec                {      stage0{         compiler}
atty                    {      stage0{         compiler}
backtrace               {      stage0{         compiler}
backtrace-sys           {      stage0{         compiler}
bitflags                {      stage0{         compiler}
byteorder               {      stage0{         compiler}
cc                      {beta, stage0{std,     compiler,codegen}, stage1{std}
cfg-if                  {beta, stage0{         compiler}
chalk-engine            {      stage0{         compiler}
chalk-macros            {      stage0{         compiler}
cmake                   {beta, stage0{std},                       stage1{std}
crossbeam-deque         {      stage0{         compiler}
crossbeam-epoch         {      stage0{         compiler}
crossbeam-utils         {      stage0{         compiler}
datafrog                {      stage0{         compiler}
dtoa                    {beta, stage0{         compiler}
either                  {      stage0{         compiler}
ena                     {      stage0{         compiler}
env_logger              {      stage0{         compiler}
filetime                {beta, stage0{         compiler}
fixedbitset             {beta, stage0{         compiler}
flate2                  {      stage0{         compiler}
getopts                 {beta, stage0{    test},                 stage1{    test}
humantime               {      stage0{         compiler}
itoa                    {beta,
jobserver               {      stage0{         compiler}
lazy_static             {beta, stage0{         compiler}
libc                    {beta, stage0{         compiler}
log                     {      stage0{         compiler}
log_settings            {      stage0{         compiler}
memoffset               {      stage0{         compiler}
miniz-sys               {      stage0{         compiler}
nodrop                  {      stage0{         compiler}
num_cpus                {beta, stage0{         compiler}
num-traits              {beta, stage0{         compiler}
ordermap                {beta, stage0{         compiler}
owning_ref              {      stage0{         compiler}
parking_lot             {      stage0{         compiler}
parking_lot_core        {      stage0{         compiler}
petgraph                {beta,
pkg-config              {      stage0{         compiler}
polonius-engine         {      stage0{         compiler}
proc-macro2             {beta,
quick-error             {      stage0{         compiler}
quote                   {beta,
rand                    {      stage0{         compiler}
remove_dir_all          {      stage0{         compiler}
rls-data                {      stage0{         compiler}
rls-span                {      stage0{         compiler}
rustc-demangle          {      stage0{         compiler}
rustc-hash              {      stage0{         compiler}
rustc-rayon             {      stage0{         compiler}
rustc-rayon-core        {      stage0{         compiler}
rustc-serialize         {      stage0{         compiler}
scoped-tls              {      stage0{         compiler}
scopeguard              {      stage0{         compiler}
serde                   {beta,
serde_derive            {beta,
serde_derive_internals  {beta,
serde_json              {beta,
smallvec                {      stage0{         compiler}
stable_deref_trait      {      stage0{         compiler}
syn                     {beta,
tempdir                 {      stage0{         compiler}
termcolor               {      stage0{         compiler}
time                    {beta,
toml                    {beta,
unicode-width           {      stage0{         compiler}
unicode-xid             {beta,
```

Internal package
----------------

```
alloc_jemalloc              {      stage0{std},                      stage1{std}
alloc                       {      stage0{std},                      stage1{std}
alloc_system                {      stage0{std},                      stage1{std}
arena                       {      stage0{         compiler}
bootstrap                   {beta,
build_helper                {beta, stage0{std,              codegen},stage1{std}
compiler_builtins           {      stage0{std},                      stage1{std}
core                        {      stage0{std},                      stage1{std}
fmt_macros                  {      stage0{         compiler}
graphviz                    {      stage0{         compiler}
libc/shim                   {      stage0{std},                      stage1{std}
panic_abort                 {      stage0{std},                      stage1{std}
panic_unwind                {      stage0{std},                      stage1{std}
proc_macro                  {      stage0{         compiler}
rustc_allocator             {      stage0{         compiler}
rustc_apfloat               {      stage0{         compiler}
rustc_asan                  {      stage0{std},                      stage1{std}
rustc_borrowck              {      stage0{         compiler}
rustc_codegen_llvm          {      stage0{                  codegen}
rustc_codegen_utils         {      stage0{         compiler}
rustc_cratesio_shim         {      stage0{         compiler}
rustc_data_structures       {      stage0{         compiler}
rustc_driver                {      stage0{         compiler}
rustc_errors                {      stage0{         compiler}
rustc_incremental           {      stage0{         compiler}
rustc_lint                  {      stage0{         compiler}
rustc_llvm                  {      stage0{                  codegen}
rustc_lsan                  {      stage0{std},                      stage1{std}
rustc-main                  {      stage0{         compiler}
rustc_metadata              {      stage0{         compiler}
rustc_mir                   {      stage0{         compiler}
rustc_msan                  {      stage0{std},                      stage1{std}
rustc_passes                {      stage0{         compiler}
rustc_platform_intrinsics   {      stage0{         compiler}
rustc_plugin                {      stage0{         compiler}
rustc_privacy               {      stage0{         compiler}
rustc_resolve               {      stage0{         compiler}
rustc_save_analysis         {      stage0{         compiler}
rustc                       {      stage0{         compiler}
rustc_target                {      stage0{         compiler}
rustc_traits                {      stage0{         compiler}
rustc_tsan                  {      stage0{std},                      stage1{std}
rustc_typeck                {      stage0{         compiler}
serialize                   {      stage0{         compiler}
std                         {      stage0{std},                      stage1{std}
std_unicode                 {      stage0{std},                      stage1{std}
syntax_ext                  {      stage0{         compiler}
syntax_pos                  {      stage0{         compiler}
syntax                      {      stage0{         compiler}
term                        {      stage0{    test},                 stage{    test}
test                        {      stage0{    test},                 stage{    test}
unwind                      {      stage0{std},                      stage1{std}
```


Copying stage1 test from stage1 (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu / x86_64-unknown-linux-gnu)
Building stage1 compiler artifacts (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu)
   Compiling nodrop v0.1.12
   Compiling cfg-if v0.1.2
   Compiling scopeguard v0.3.3
   Compiling lazy_static v1.0.0
   Compiling memoffset v0.2.1
   Compiling libc v0.2.40
   Compiling rustc-rayon-core v0.1.0
   Compiling stable_deref_trait v1.0.0
   Compiling smallvec v0.6.0
   Compiling either v1.5.0
   Compiling byteorder v1.2.2
   Compiling bitflags v1.0.1
   Compiling serialize v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libserialize)
   Compiling scoped-tls v0.1.1
   Compiling pkg-config v0.3.9
   Compiling rustc_target v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_target)
   Compiling unicode-width v0.1.4
   Compiling cc v1.0.15
   Compiling termcolor v0.3.6
   Compiling syntax v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libsyntax)
   Compiling lazy_static v0.2.11
   Compiling rustc-demangle v0.1.7
   Compiling remove_dir_all v0.5.1
   Compiling datafrog v0.1.0
   Compiling rustc v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc)
   Compiling rustc-serialize v0.3.24
   Compiling fmt_macros v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libfmt_macros)
   Compiling graphviz v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libgraphviz)
   Compiling rustc_metadata v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_metadata)
   Compiling rustc_incremental v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_incremental)
   Compiling rustc_platform_intrinsics v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_platform_intrinsics)
   Compiling quick-error v1.2.1
   Compiling rustc_driver v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_driver)
   Compiling ar v0.3.1
   Compiling crossbeam-utils v0.2.2
   Compiling log v0.4.1
   Compiling arrayvec v0.4.7
   Compiling owning_ref v0.3.3
   Compiling chalk-macros v0.1.0
   Compiling log_settings v0.1.1
   Compiling humantime v1.1.1
   Compiling rustc_cratesio_shim v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_cratesio_shim)
   Compiling ena v0.9.3
   Compiling rustc_apfloat v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_apfloat)
   Compiling rustc-hash v1.0.1
   Compiling crossbeam-epoch v0.3.1
   Compiling chalk-engine v0.6.0
   Compiling polonius-engine v0.4.0
   Compiling num_cpus v1.8.0
   Compiling rand v0.4.2
   Compiling atty v0.2.8
   Compiling jobserver v0.1.11
   Compiling crossbeam-deque v0.2.0
   Compiling env_logger v0.5.8
   Compiling parking_lot_core v0.2.14
   Compiling tempdir v0.3.7
   Compiling parking_lot v0.5.5
   Compiling rustc-rayon v0.1.0
   Compiling backtrace-sys v0.1.22
   Compiling miniz-sys v0.1.10
   Compiling rustc_data_structures v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_data_structures)
   Compiling flate2 v1.0.1
   Compiling rls-span v0.4.0
   Compiling backtrace v0.3.6
   Compiling rls-data v0.16.0
   Compiling arena v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libarena)
   Compiling syntax_pos v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libsyntax_pos)
   Compiling rustc_errors v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_errors)
   Compiling proc_macro v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libproc_macro)
   Compiling syntax_ext v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/libsyntax_ext)
   Compiling rustc_typeck v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_typeck)
   Compiling rustc_mir v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_mir)
   Compiling rustc_traits v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_traits)
   Compiling rustc_allocator v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_allocator)
   Compiling rustc_resolve v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_resolve)
   Compiling rustc_plugin v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_plugin)
   Compiling rustc_save_analysis v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_save_analysis)
   Compiling rustc_privacy v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_privacy)
   Compiling rustc_codegen_utils v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_codegen_utils)
   Compiling rustc_borrowck v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_borrowck)
   Compiling rustc_lint v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_lint)
   Compiling rustc_passes v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_passes)
   Compiling rustc-main v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/rustc)
    Finished release [optimized] target(s) in 4m 56.45s
Copying stage1 rustc from stage1 (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu / x86_64-unknown-linux-gnu)
Building stage1 codegen artifacts (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu, llvm)
   Compiling build_helper v0.1.0 (file:///home/prataprc/myworld/devgit/rust/src/build_helper)
   Compiling rustc_codegen_llvm v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_codegen_llvm)
   Compiling cc v1.0.15
   Compiling rustc_llvm v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustc_llvm)
    Finished release [optimized] target(s) in 40.41s
Assembling stage2 compiler (x86_64-unknown-linux-gnu)
Uplifting stage1 std (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu)
Copying stage2 std from stage1 (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu / x86_64-unknown-linux-gnu)
Uplifting stage1 test (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu)
Copying stage2 test from stage1 (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu / x86_64-unknown-linux-gnu)
Uplifting stage1 rustc (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu)
Copying stage2 rustc from stage1 (x86_64-unknown-linux-gnu -> x86_64-unknown-linux-gnu / x86_64-unknown-linux-gnu)
Building rustdoc for stage2 (x86_64-unknown-linux-gnu)
   Compiling void v1.0.2
   Compiling libc v0.2.40
   Compiling ucd-util v0.1.1
   Compiling lazy_static v1.0.0
   Compiling regex v0.2.10
   Compiling pulldown-cmark v0.1.2
   Compiling utf8-ranges v1.0.0
   Compiling bitflags v0.9.1
   Compiling remove_dir_all v0.5.1
   Compiling unreachable v1.0.0
   Compiling thread_local v0.3.5
   Compiling regex-syntax v0.5.5
   Compiling memchr v2.0.1
   Compiling rand v0.4.2
   Compiling aho-corasick v0.6.4
   Compiling tempdir v0.3.7
   Compiling minifier v0.0.11
   Compiling rustdoc v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/librustdoc)
   Compiling rustdoc-tool v0.0.0 (file:///home/prataprc/myworld/devgit/rust/src/tools/rustdoc)
    Finished release [optimized] target(s) in 47.83s
Build completed successfully in 0:21:43
