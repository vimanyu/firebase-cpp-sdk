# Overview

(TODO: Describe C++ SDK and its scope)

## Integration with FPL

(TODO: Describe how this is integrated with FPL, architecture overview and
useful commands)

## Copybara process

(TODO: Describe how github C++ code is copied here, what is not copied, and how
to run the copybara)

## Running integration tests

Given the C++ SDK runs on a lot of platforms, there are many different setups we
can use to run its integration tests. Below are instructions on how to run them
with all possible setups.

### Against Firestore emulator

This is the preferred way to run integration tests. The way it is configured is
we have a controlling `go_test` (`integration_test_emulator.go`), which will
pull Firestore emulator as a `data` dependency and set it up before it finds and
runs the actual integration tests in separate processes.

Note this means on mobile platforms, the integration tests are run within
simulation, as there is no way to setup Firestore emulator if they are run on
real devices.

#### iOS (running within iOS simulator on forge-on-mac, hence `darwin_x86_64`):

(TODO: When tests fail, the messages are not properly formatted, especially
newline is turned into '\n'.)

```bash
blaze test --config=darwin_x86_64 //firebase/firestore/client/cpp:ios_integration_tests
```

#### Android (running within Android emulator, requires kvm to run on google3):

(TODO: When tests fail, the messages only tell you the test failed, because of
the JUnit test wrapping. Ideally we should fix that.)

```bash
blaze --blazerc=//google/src/head/depot/google3/java/com/google/android/gmscore/blaze/blazerc \
  test --define=firebase_build=head --config=gmscore_x86 \
  //firebase/firestore/client/cpp:android_integration_tests \
  --experimental_one_version_enforcement=warning
```

Support for other platforms is not available yet.

### Against Firestore prod backend

Running against the actual Firestore backend takes much longer and sometimes our
tests might get to run in an environment where external network connection is
impossible (such as Forge).

It is useful still, for example, to run it before a release or to debug issues
that only happen with real backend.

#### iOS (Runs on real devices via MobileHarness):

```bash
blaze test --config=ios_fat --notest_loasd //firebase/firestore/client/cpp:ios_integration_tests_mh
```

#### Android:

(TODO: Right now, running below would not succeed, there needs to be a hack to
fix the gmscore version built on rabbit first, eliminate the hack)

```bash
blaze --blazerc=//google/src/head/depot/google3/java/com/google/android/gmscore/blaze/blazerc \
test --define=firebase_build=head --config=gmscore_x86 \
//firebase/firestore/client/cpp:android_integration_tests_prod \
--experimental_one_version_enforcement=warning
```