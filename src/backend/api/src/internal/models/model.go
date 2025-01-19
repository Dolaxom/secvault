package models

type SecretWriteRequest struct {
	Secret   string `json:"secret"`
	Password string `json:"password"`
}

type SecretWriteResponse struct {
	FirstToken  string `json:"first"`
	SecondToken string `json:"second"`
}

type SecretReadRequest struct {
	FirstToken  string `json:"first"`
	SecondToken string `json:"second"`
}

type SecretReadResponse struct {
	Secret string `json:"secret"`
}
