import pygame
pygame.init()

# Set up the display
win = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Pong Game")

# Set up the paddles
paddle1 = pygame.Rect(50, 250, 20, 100)
paddle2 = pygame.Rect(730, 250, 20, 100)

# Set up the ball
ball = pygame.Rect(390, 290, 20, 20)
ball_speed_x = 7
ball_speed_y = 7

# Set up the colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Game loop
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()

    # Move the paddles
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w] and paddle1.y > 0:
        paddle1.y -= 5
    if keys[pygame.K_s] and paddle1.y < 500:
        paddle1.y += 5
    if keys[pygame.K_UP] and paddle2.y > 0:
        paddle2.y -= 5
    if keys[pygame.K_DOWN] and paddle2.y < 500:
        paddle2.y += 5

    # Move the ball
    ball.x += ball_speed_x
    ball.y += ball_speed_y
    if ball.top <= 0 or ball.bottom >= 600:
        ball_speed_y *= -1
    if ball.left <= 0 or ball.right >= 800:
        ball_speed_x *= -1

    # Check for collision between ball and paddles
    if ball.colliderect(paddle1) or ball.colliderect(paddle2):
        ball_speed_x *= -1

    # Draw the paddles and ball
    win.fill(BLACK)
    pygame.draw.rect(win, WHITE, paddle1)
    pygame.draw.rect(win, WHITE, paddle2)
    pygame.draw.ellipse(win, WHITE, ball)

    # Update the display
    pygame.display.update()
