import os
import whisper
from flask import Flask, request

UPLOADS_FOLDER = "C:\\Dev\\transcriby\\transcriby-server\\.local"

app = Flask(__name__)
model = whisper.load_model("base", "cpu")


@app.post("/")
def upload_passage():
    if "passage" not in request.files:
        return "Error: No file part", 400
    passage = request.files["passage"]

    if passage.filename == "":
        return "Error: Empty file part", 400
    else:
        filename = passage.filename
        filepath = os.path.join(os.path.join(UPLOADS_FOLDER), filename)
        passage.save(filepath)
        result = model.transcribe(filepath)
        return result["text"], 200


if __name__ == "__main__":
    app.run()
