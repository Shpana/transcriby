import os
from flask import Flask, request

UPLOADS_FOLDER = "C:\\Dev\\transcriby\\transcriby\\server\\.uploads"

app = Flask(__name__)


@app.post("/<user_name>")
def upload_passage(user_name: str):
    if "passage" not in request.files:
        return "No file part", 400
    passage = request.files["passage"]

    if passage.filename == "":
        return "Empty file part", 400
    else:
        filename = passage.filename
        user_upload_folder = os.path.join(UPLOADS_FOLDER, hash(user_name))
        os.mkdir(user_upload_folder)
        passage.save(os.path.join(user_upload_folder, filename))
        return "Success", 201


if __name__ == "__main__":
    app.run()
