# Contributing

## Branches

- Create branches off `main` named `<github-user>/<short-topic>`.
- Never push directly to `main`. All changes reach `main` through a pull request.

## Pull requests

- Aim for one issue per PR. Put `Closes #N` in the description so the issue closes when the PR merges.
- Before merging, a PR needs at least one approving review and passing tests.
- Squash-merge into `main` so its history stays linear.
- Keep PRs small enough to review in one sitting. Split larger work into several PRs.

## Code style

- Follow the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
- Use [cppreference.com](https://en.cppreference.com) as the reference for the language and standard library.
- Put all library code in namespace `img`.

## Tests

- Every public function has at least one GoogleTest test in `tests/`.
- A bug fix should include a regression test that fails before the fix and passes after it.
- Run the full test suite before opening a PR and again before merging.

## Building and running tests

Configure, build, and run the tests from the repository root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
