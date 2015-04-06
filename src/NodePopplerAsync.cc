#include <nan.h>
#include <QtCore/QBuffer>
#include "NodePoppler.h"

using v8::Function;
using v8::Local;
using v8::Null;
using v8::Number;
using v8::Value;
using v8::Object;
using v8::String;
using v8::Array;
using namespace std;

class PdfWriteWorker : public NanAsyncWorker {
  public:
    PdfWriteWorker(NanCallback *callback, struct WriteFieldsParams params)
      : NanAsyncWorker(callback), params(params) {}
    ~PdfWriteWorker() {}

    // Executed inside the worker-thread.
    // It is not safe to access V8, or V8 data structures
    // here, so everything we need for input and output
    // should go on `this`.
    void Execute () {
      buffer = writePdfFields(params);
    }

    // Executed when the async work is complete
    // this function will be run inside the main event loop
    // so it is safe to use V8 again
    void HandleOKCallback () {
      NanScope();
      Local<Value> argv[] = {
          NanNull()
        , NanNewBufferHandle(buffer->data().data(), buffer->size())
      };

      callback->Call(2, argv);
    }

  private:
    QBuffer *buffer;
    WriteFieldsParams params;
};

// Asynchronous access to the `writePdfFields` function
NAN_METHOD(WriteAsync) {
  NanScope();

  WriteFieldsParams params = v8ParamsToCpp(args);

  NanCallback *callback = new NanCallback(args[3].As<Function>());
  
  NanAsyncQueueWorker(new PdfWriteWorker(callback, params));
  NanReturnUndefined();
}