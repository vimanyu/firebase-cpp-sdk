#ifndef FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_DOCUMENT_CHANGE_ANDROID_H_
#define FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_DOCUMENT_CHANGE_ANDROID_H_

#include <cstdint>
#include <string>

#include "firestore/src/android/wrapper.h"
#include "firestore/src/include/firebase/firestore/document_change.h"

namespace firebase {
namespace firestore {

class DocumentChangeInternal : public Wrapper {
 public:
  using ApiType = DocumentChange;
  using Wrapper::Wrapper;

  DocumentChange::Type type() const;
  DocumentSnapshot document() const;
  std::size_t old_index() const;
  std::size_t new_index() const;

 private:
  friend class FirestoreInternal;

  static bool Initialize(App* app);
  static void Terminate(App* app);
};

}  // namespace firestore
}  // namespace firebase

#endif  // FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_DOCUMENT_CHANGE_ANDROID_H_
