#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a song node
typedef struct Song {
    char title[100];
    struct Song* next;
} Song;

// Define a structure for the playlist
typedef struct Playlist {
    Song* head;
    Song* tail;
} Playlist;

// Initialise an empty playlist
void initialisePlaylist(Playlist* playlist) {
    playlist->head = NULL;
    playlist->tail = NULL;
}

// Add a song to the end of the playlist (enqueue)
void addSongToPlaylist(Playlist* playlist, const char* title) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (newSong == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newSong->title, title);
    newSong->next = NULL;

    if (playlist->tail == NULL) {
        // If the playlist is empty, set both head and tail to the new song
        playlist->head = newSong;
        playlist->tail = newSong;
    } else {
        // Otherwise, add the new song to the end of the playlist
        playlist->tail->next = newSong;
        playlist->tail = newSong;
    }
}

// Play the next song in the playlist (dequeue)
void playNextSong(Playlist* playlist) {
    if (playlist->head == NULL) {
        printf("Playlist is empty. Add songs to the playlist.\n");
        return;
    }

    Song* currentSong = playlist->head;
    printf("Now playing: %s\n", currentSong->title);
    playlist->head = currentSong->next;
    free(currentSong);

    if (playlist->head == NULL) {
        // If the playlist becomes empty after playing the song, update the tail
        playlist->tail = NULL;
    }
}

int main() {
    Playlist myPlaylist;
    initialisePlaylist(&myPlaylist);

    int choice;
    char songTitle[100];

    while (1) {
        printf("Playlist Manager Menu:\n");
        printf("1. Add a song to the playlist\n");
        printf("2. Play the next song\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the title of the song: ");
                scanf("%s", songTitle);
                addSongToPlaylist(&myPlaylist, songTitle);
                printf("Song '%s' added to the playlist.\n", songTitle);
                break;
            case 2:
                playNextSong(&myPlaylist);
                break;
            case 3:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
