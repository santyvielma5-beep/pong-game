<!--  
#if 0
-->
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Pong JS para Emular</title>
    <style>
        body { background-color: #111; color: white; text-align: center; font-family: sans-serif; margin: 0; padding: 10px; }
        canvas { background-color: #000; border: 4px solid #fff; display: block; margin: 10px auto; }
    </style>
</head>
<body>
    <h3>Controles: W/S (Izquierda) | Flechas Arriba/Abajo (Derecha)</h3>
    <canvas id="pongCanvas" width="800" height="450"></canvas>
    <script>
        const canvas = document.getElementById("pongCanvas");
        const ctx = canvas.getContext("2d");
        const paddleWidth = 15, paddleHeight = 80, paddleSpeed = 6;
        let leftY = (canvas.height - paddleHeight) / 2, rightY = (canvas.height - paddleHeight) / 2;
        let ballX = canvas.width / 2, ballY = canvas.height / 2, ballRadius = 10, ballSpeedX = 5, ballSpeedY = 5;
        let leftScore = 0, rightScore = 0;
        const keys = {};
        window.addEventListener("keydown", (e) => keys[e.key] = true);
        window.addEventListener("keyup", (e) => keys[e.key] = false);
        function resetBall(direction) {
            ballX = canvas.width / 2; ballY = canvas.height / 2;
            ballSpeedX = 5 * direction; ballSpeedY = (Math.random() > 0.5 ? 5 : -5);
        }
        function update() {
            if (keys["w"] || keys["W"]) leftY = Math.max(0, leftY - paddleSpeed);
            if (keys["s"] || keys["S"]) leftY = Math.min(canvas.height - paddleHeight, leftY + paddleSpeed);
            if (keys["ArrowUp"]) rightY = Math.max(0, rightY - paddleSpeed);
            if (keys["ArrowDown"]) rightY = Math.min(canvas.height - paddleHeight, rightY + paddleSpeed);
            ballX += ballSpeedX; ballY += ballSpeedY;
            if (ballY - ballRadius <= 0 || ballY + ballRadius >= canvas.height) ballSpeedY *= -1;
            if (ballX - ballRadius <= 30 + paddleWidth && ballX - ballRadius >= 30) {
                if (ballY >= leftY && ballY <= leftY + paddleHeight) { ballSpeedX *= -1; ballX = 30 + paddleWidth + ballRadius; }
            }
            if (ballX + ballRadius >= canvas.width - 30 - paddleWidth && ballX + ballRadius <= canvas.width - 30) {
                if (ballY >= rightY && ballY <= rightY + paddleHeight) { ballSpeedX *= -1; ballX = canvas.width - 30 - paddleWidth - ballRadius; }
            }
            if (ballX < 0) { rightScore++; resetBall(1); } else if (ballX > canvas.width) { leftScore++; resetBall(-1); }
        }
        function draw() {
            ctx.fillStyle = "#000"; ctx.fillRect(0, 0, canvas.width, canvas.height);
            ctx.strokeStyle = "#444"; ctx.lineWidth = 2; ctx.beginPath();
            ctx.moveTo(canvas.width / 2, 0); ctx.lineTo(canvas.width / 2, canvas.height); ctx.stroke();
            ctx.fillStyle = "#fff"; ctx.fillRect(30, leftY, paddleWidth, paddleHeight);
            ctx.fillRect(canvas.width - 30 - paddleWidth, rightY, paddleWidth, paddleHeight);
            ctx.beginPath(); ctx.arc(ballX, ballY, ballRadius, 0, Math.PI * 2); ctx.fill();
            ctx.font = "40px sans-serif"; ctx.fillStyle = "#aaa";
            ctx.fillText(leftScore, canvas.width / 4, 50); ctx.fillText(rightScore, (canvas.width / 4) * 3, 50);
        }
        function loop() { update(); draw(); requestAnimationFrame(loop); }
        loop();
    </script>
</body>
</html>
<!--
#endif
#include "raylib.h"
int main() {
    const int screenWidth = 800; const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pong Nativo C++");
    float paddleHeight = 80, paddleWidth = 15, paddleSpeed = 5.0f;
    Vector2 leftPaddlePos = { 30, (screenHeight / 2) - (paddleHeight / 2) };
    Vector2 rightPaddlePos = { screenWidth - 30 - paddleWidth, (screenHeight / 2) - (paddleHeight / 2) };
    Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f }; Vector2 ballSpeed = { 5.0f, 5.0f }; float ballRadius = 10.0f;
    int leftScore = 0, rightScore = 0; SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W) && leftPaddlePos.y > 0) leftPaddlePos.y -= paddleSpeed;
        if (IsKeyDown(KEY_S) && leftPaddlePos.y < screenHeight - paddleHeight) leftPaddlePos.y += paddleSpeed;
        if (IsKeyDown(KEY_UP) && rightPaddlePos.y > 0) rightPaddlePos.y -= paddleSpeed;
        if (IsKeyDown(KEY_DOWN) && rightPaddlePos.y < screenHeight - paddleHeight) rightPaddlePos.y += paddleSpeed;
        ballPos.x += ballSpeed.x; ballPos.y += ballSpeed.y;
        if (ballPos.y <= ballRadius || ballPos.y >= screenHeight - ballRadius) ballSpeed.y *= -1.0f;
        if (CheckCollisionCircleRec(ballPos, ballRadius, {leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight})) ballSpeed.x *= -1.0f;
        if (CheckCollisionCircleRec(ballPos, ballRadius, {rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight})) ballSpeed.x *= -1.0f;
        if (ballPos.x <= 0) { rightScore++; ballPos = { screenWidth / 2.0f, screenHeight / 2.0f }; ballSpeed.x = 5.0f; }
        if (ballPos.x >= screenWidth) { leftScore++; ballPos = { screenWidth / 2.0f, screenHeight / 2.0f }; ballSpeed.x = -5.0f; }
        BeginDrawing(); ClearBackground(BLACK);
        DrawRectangleV(leftPaddlePos, { paddleWidth, paddleHeight }, WHITE); DrawRectangleV(rightPaddlePos, { paddleWidth, paddleHeight }, WHITE);
        DrawCircleV(ballPos, ballRadius, WHITE); DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, DARKGRAY);
        DrawText(TextFormat("%i", leftScore), screenWidth / 4 - 20, 20, 40, LIGHTGRAY); DrawText(TextFormat("%i", rightScore), screenWidth * 3 / 4 - 20, 20, 40, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow(); return 0;
}
-->
