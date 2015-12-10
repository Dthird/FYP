CREATE TABLE user_info
(
    user_id TEXT PRIMARY KEY,
    pwd TEXT NOT NULL,
    attempts INTEGER NOT NULL DEFAULT 2,
    privilege INTEGER NOT NULL DEFAULT 0,
    result_history DOUBLE DEFAULT 0,
    result_uploaded DOUBLE DEFAULT 0
);
